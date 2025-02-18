#!/bin/bash

# Error log file
ERROR_LOG="errors.log"
> "$ERROR_LOG"  # Clearing the contents of error log if present

# Help function using Here Document
show_help(){
    cat <<EOF
Usage: $0 [OPTIONS]

Options:
  -d <directory>  Search for a keyword recursively in a directory.
  -f <file>       Search for a keyword in a specific file.
  -k <keyword>    Keyword to search.
  --help          Display this help menu.

Examples:
  ./file_analyzer.sh -d logs -k error
  ./file_analyzer.sh -f script.sh -k TODO
EOF
}

# Input Validation Function
validate_input(){
    local file=$1
    local keyword=$2

    # Checking if file exists
    if [[ -n "$file" && ! -f "$file" ]]; then
        echo "ERROR: File '$file' does not exist." | tee -a "$ERROR_LOG"
        exit 1
    fi

    # Check if keyword is valid (non-empty and only alphanumeric or underscore)
    if [[ -z "$keyword" || ! "$keyword" =~ ^[a-zA-Z0-9_]+$ ]]; then
        echo "ERROR: Invalid or empty keyword." | tee -a "$ERROR_LOG"
        exit 1
    fi
}

#checking if help is given
if [[ "$1" == "--help" ]]; then 
    show_help
    exit 0
fi

# parsing command-line arguments using getopts
while getopts ":d:f:k:h" opt; do
    case "$opt" in
        d) directory=$OPTARG ;;
        f) file=$OPTARG ;;
        k) keyword=$OPTARG ;;
        h) show_help ; exit 0 ;;
        *) echo "ERROR: Invalid option: -$OPTARG" | tee -a "$ERROR_LOG" ; exit 1 ;;
    esac
done

# Check if no arguments are provided
if [[ "$#" -eq 0 ]]; then
    echo "ERROR: No keyword or file specified." | tee -a "$ERROR_LOG"
    exit 1
fi

# Function call to validate inputs
validate_input "$file" "$keyword"

# Recursive function to search for a keyword in files within a directory and its subdirectories
search_recursive(){
    local dir="$1"
    local keyword="$2"
    for file in "$dir"/*; do
        if [[ -d "$file" ]]; then
            search_recursive "$file" "$keyword"  # Recursively search subdirectories
        elif [[ -f "$file" ]]; then
            if grep -q "$keyword" "$file" 2>> "$ERROR_LOG"; then
                echo "Keyword found in file: $file"
            fi
        fi
    done
}

# Search operation for directory
if [[ -n "$directory" ]]; then
    if [[ -d "$directory" ]]; then
        # Recursively search the directory
        search_recursive "$directory" "$keyword"
    else
        echo "ERROR: Directory '$directory' doesn't exist." | tee -a "$ERROR_LOG"
        exit 1
    fi
# Search operation for file
elif [[ -n "$file" ]]; then
    if grep -q "$keyword" <<<"$(cat "$file")" 2>> "$ERROR_LOG"; then
        echo "Keyword found in file: $file"
    else
        echo "No match found in file: $file"
    fi
fi


# Exit status handling (exit status of the last command)
echo "Script executed with exit status: $?"
