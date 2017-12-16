#!/bin/sh

echo "Detecting architecture...";
MACHINE_MTYPE="$(uname -m)";
ARCH="${MACHINE_MTYPE}";
REPOSITORY_NAME="headmelted";

if [ "$ARCH" = "amd64" ]; then REPOSITORY_NAME="Microsoft"; fi;

echo "Architecture detected as ${ARCH}...";

if [ "${REPOSITORY_NAME}" = "headmelted" ]; then

  # echo "Installing bintray GPG key...";
  # apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 379CE192D401AB61;
  # echo "Done!";

  echo "Installing headmelted GPG key...";
  wget -qO - https://packagecloud.io/headmelted/codebuilds/gpgkey | apt-key add -;
  echo "Done!";
  
else

  echo "Retrieving Microsoft GPG key...";
  curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg;
  
  echo "Installing Microsoft GPG key...";
  mv microsoft.gpg /etc/apt/trusted.gpg.d/microsoft.gpg;
  
fi;

echo "Installing ${REPOSITORY_NAME} repository...";

if [ "${REPOSITORY_NAME}" = "headmelted" ]; then
  echo "deb https://packagecloud.io/headmelted/codebuilds/ubuntu/ xenial main" | sudo tee -a /etc/apt/sources.list.d/codebuilds.list;
else
  echo "deb https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list;
fi;

if [ $? -eq 0 ]; then
  echo "Repository install complete.";
else
  echo "Repository install failed.";
  exit 1;
fi;

echo "Updating APT cache..."
apt-get update;
echo "Done!"

echo "Installing Visual Studio Code...";

CODE_EXECUTABLE_NAME="";
if [ "${REPOSITORY_NAME}" = "headmelted" ]; then
  CODE_EXECUTABLE_NAME="code-oss";
else
  CODE_EXECUTABLE_NAME="code-insiders";
fi;

if [ "${ARCH}" = "aarch64" ]; then
  echo "aarch64 currently disabled. THIS IS BEING WORKED ON, APOLOGIES FOR THE INCONVENIENCE, PLEASE CHECK https://code.headmelted.com FOR UPDATES";
  exit 1;
else
  apt-get install -y ${CODE_EXECUTABLE_NAME} --allow-unauthenticated;
fi

if [ $? -eq 0 ]; then
  echo "Visual Studio Code install complete.";
else
  echo "Visual Studio Code install failed.";
  exit 1;
fi;

echo "Installing git...";
apt-get install -y git;
if [ $? -eq 0 ]; then
  echo "git install complete.";
else
  echo "git install failed.";
  exit 1;
fi;

echo "Installing any dependencies that may have been missed...";
apt-get install -y -f;
if [ $? -eq 0 ]; then
  echo "Missed dependency install complete.";
else
  echo "Missed dependency install failed.";
  exit 1;
fi;

echo "

Installation complete!

You can start code at any time by calling \"${CODE_EXECUTABLE_NAME}\" within a terminal.

A shortcut should also now be available in your desktop menus (depending on your distribution).

";

