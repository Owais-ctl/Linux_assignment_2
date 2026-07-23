#!/bin/bash
# process_submissions.sh

SUBMISSION_DIR="submissions"
BACKUP_DIR="backup"
REPORT="report.txt"
ERRORS="errors.log"

# Create backup directory and initialize log files
mkdir -p "$BACKUP_DIR" 2>> "$ERRORS"
> "$REPORT"
> "$ERRORS"

declare -A seen_hashes
processed=0
duplicates=0
backed_up=0

for file in "$SUBMISSION_DIR"/*; do
    if [ -f "$file" ]; then
        ((processed++))
        
        # Calculate MD5 hash to identify unique file content
        file_hash=$(md5sum "$file" 2>> "$ERRORS" | awk '{print $1}')
        
        if [[ -n "${seen_hashes[$file_hash]}" ]]; then
            ((duplicates++))
        else
            seen_hashes[$file_hash]=1
            cp "$file" "$BACKUP_DIR/" 2>> "$ERRORS"
            ((backed_up++))
        fi
    fi
done

# Output summary metrics
{
    echo "Files Processed: $processed"
    echo "Duplicates Found: $duplicates"
    echo "Files Backed Up (Unique): $backed_up"
} > "$REPORT"

echo "Processing complete. Summary saved to $REPORT. Check $ERRORS for issues."