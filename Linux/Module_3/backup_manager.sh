#!/bin/bash

#check if 3 args are provided
if [ $# -ne 3 ]; then
    echo " Provide 3 argugemts .( $0 <sourcedirectory> <backupdirectory> <fileext> )"
    exit 1
fi

SOURCE_DIRECTORY=$1
BACKUP_DIRECTORY=$2
FILE_EXT=$3

#checking if source dir exists
if [ ! -d $SOURCE_DIRECTORY ]; then
    echo "Source directory dosen't exists"
    exit 1
fi

#checking if backup dir exists
if [ ! -d $BACKUP_DIRECTORY ]; then
    echo "Creating backup directory $BACKUP_DIRECTORY"
    mkdir -p $BACKUP_DIRECTORY || { echo "ERROR : Failed to create backup directory "; exit 1; }
fi

#using globbing to find files with specific file formats
FILES=("$SOURCE_DIRECTORY"/*"$FILE_EXT")

if [ ${#FILES[@]} -eq 0 ]; then
    echo "No files found with the given extension $FILE_EXT found in $SOURCE_DIRECTORY"
    exit 0
fi

export BACKUP_COUNT=0
TOTAL_SIZE=0

#storing the list of files in an array and printing them before backup
echo "Files to be backedup"
for file in "${FILES[@]}"; do
    if [ -f "$file" ]; then
        size=$(stat --format=%s "$file")
        echo "$file - $size bytes"
        TOTAL_SIZE=$((TOTAL_SIZE + size))
    fi
done

#Backing up
for file in "${FILES[@]}"; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        backupfile="$BACKUP_DIRECTORY/$filename"

        #checking if file already exists at backup location
        if [ -f "$backupfile" ]; then
            if [ "$file" -nt "$backupfile" ]; then #compare timestamp and overwrite iff file is newer
                cp "$file" "$backupfile"
                echo " Overwritten : $filename"
                BACKUP_COUNT=$((BACKUP_COUNT + 1))
            else
                echo "No change : $filename"
            fi
        else #if file not exists already
            cp "$file" "$backupfile"
            echo "Backed up $filename"
            BACKUP_COUNT=$((BACKUP_COUNT + 1))
        fi
    fi
done 

#Log
REPORT_LOG="$BACKUP_DIRECTORY/backup_report.log"

echo "Backup summary report

Total files processed = $BACKUP_COUNT
Total size of files backed up = $TOTAL_SIZE
The path to the backup directory = $BACKUP_DIRECTORY
"  > "$REPORT_LOG"

echo "Backup completed and report saved to $REPORT_LOG"