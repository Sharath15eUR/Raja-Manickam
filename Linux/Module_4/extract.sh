#!/bin/bash

# Check if input file is given
if [ -z "$1" ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

INPUT_FILE="$1"
OUTPUT_FILE="$HOME/Desktop/output.txt"

>"$OUTPUT_FILE" # clearing the output file


# extracting the required parameters
grep -E '"frame.time"|"wlan.fc.type"|"wlan.fc.subtype"' "$INPUT_FILE" | sed 's/^\s*//' > "$OUTPUT_FILE"


echo "Extraction completed. Output saved in '$OUTPUT_FILE'"
