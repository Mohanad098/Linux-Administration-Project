#!/bin/bash

# Define variables for the directory, files, and new user home directory for the previously defined user
DIR="project_dir"
FILES=("main.c" "main.h" "hello.c" "hello.h")
TAR_FILE="project_dir.tar"
NEW_USER_HOME="/home/mostafa"
USERNAME="mostafa"
USERPASS="mos123"
GROUPNAME="ASU"
USER_CREATION_BASH="userdef"

# Check if the directory we want to create already exists, and if it does, remove it
[ -d "$DIR" ] && rm -rf "$DIR"

# Create the directory & create 4 files in this directory (main.c, main.h, hello.c, hello.h)
mkdir "$DIR" && touch "$DIR"/{main.c,main.h,hello.c,hello.h}

# Loop through each file and write its name in the file
for file in "${FILES[@]}"; do 
    echo "This file is named $file" > "$DIR/$file"
done

# Compress the directory into a tar file
tar -cf "$TAR_FILE" "$DIR"

# Check if the home directory exists
if [ ! -d "$NEW_USER_HOME" ]; then
    echo "Home directory for $USERNAME does not exist."
    echo "Running the user creation script to create the user and home directory."
    
    # Run the user creation script to ensure the user and home directory are created
    sudo $USER_CREATION_BASH $USERNAME $USERPASS $GROUPNAME
    
    # Check again if the home directory exists after running the script
    if [ ! -d "$NEW_USER_HOME" ]; then
        echo "Failed to create home directory for $USERNAME."
        exit 1
    fi
fi

# Copy the tar file to the new user's home directory and extract it there
sudo -u $USERNAME bash -c "
cp \"$TAR_FILE\" \"$NEW_USER_HOME\" && \
cd \"$NEW_USER_HOME\" && \
tar -xvf \"$TAR_FILE\"
"

# Print that operation done successfully
echo "Copying files to $NEW_USER_HOME done successfully!"

