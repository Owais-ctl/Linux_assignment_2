# Question 1: Submission Batch Processor

## Command Execution Sequence
mkdir -p submissions
echo "hello" > submissions/file1.txt
echo "hello" > submissions/file2.txt
echo "world" > submissions/file3.txt

chmod +x process_submissions.sh
./process_submissions.sh
cat report.txt