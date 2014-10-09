#
# Copyright (C) 2012 The Android Open-Source Project
# Copyright (C) 2014  Rudolf Tammekivi <rtammekivi@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

import sha
import re
import os

import common

# Replaces /system/etc/install-cm-recovery.sh with our variant.
def ReplaceRecoveryInstall(info):
	"""Generate a binary patch that creates the recovery image starting
	with the boot image.  (Most of the space in these images is just the
	kernel, which is identical for the two, so the resulting patch
	should be efficient.)  Add it to the output zip, along with a shell
	script that is run from init.rc on first boot to actually do the
	patching and install the new recovery image.

	recovery_img and boot_img should be File objects for the
	corresponding images.  info should be the dictionary returned by
	common.LoadInfoDict() on the input target_files.

	Returns an Item for the shell script, which must be made
	executable.
	"""

	diff_program = ["imgdiff"]
	path = os.path.join(info.input_tmp, "SYSTEM", "etc", "recovery-resource.dat")
	if os.path.exists(path):
		diff_program.append("-b")
		diff_program.append(path)
		bonus_args = "-b /system/etc/recovery-resource.dat"
	else:
		bonus_args = ""

	boot_img = common.GetBootableImage("boot.img", "boot.img",
																		 info.input_tmp, "BOOT")
	recovery_img = common.GetBootableImage("recovery.img", "recovery.img",
																		 info.input_tmp, "RECOVERY")

	boot_device = "/cust/image/boot.img"
	recovery_device = "/cust/image/recovery.img"

	sh = """#!/system/bin/sh
if ! applypatch -c %(recovery_device)s %(recovery_sha1)s; then
	log -t recovery "Installing new recovery image"
	mount -o rw,remount /cust
	applypatch %(bonus_args)s %(boot_device)s %(recovery_device)s %(recovery_sha1)s %(recovery_size)d %(boot_sha1)s:/system/recovery-from-boot.p
	mount -o ro,remount /cust
else
	log -t recovery "Recovery image already installed"
fi
""" % { 'boot_size': boot_img.size,
				'boot_sha1': boot_img.sha1,
				'recovery_size': recovery_img.size,
				'recovery_sha1': recovery_img.sha1,
				'boot_device': boot_device,
				'recovery_device': recovery_device,
				'bonus_args': bonus_args,
				}
	common.ZipWriteStr(info.output_zip, "recovery/etc/install-cm-recovery.sh", sh)

# Function used to write the boot/recovery image to the corresponding location.
def InstallImage(info, mount_point, location, file):
	info.script.Mount(mount_point)
	args = {'file': file, 'location': location}
	info.script.AppendExtra(
		'package_extract_file("%(file)s", "%(location)s/%(file)s");' % args)

# Function used to copy boot/recovery image to the /cust (/boot) partition.
def InstallCustImage(info, file):
	InstallImage(info, "/boot", "/boot/image", file)

# Function called after flashing the main system is complete.
def FullOTA_InstallEnd(info):
	# Manually remove boot.img direct install done by releasetools.
	# This removal is done before installing cust image.
	edify = info.script
	for cmd in edify.script:
		if "package_extract_file(\"boot.img\"" in cmd:
			edify.script.remove(cmd)
	InstallCustImage(info, "boot.img")
	ReplaceRecoveryInstall(info)
