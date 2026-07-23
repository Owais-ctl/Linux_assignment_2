Question 4: Real-Time Stream Monitoring Pipeline


### Terminal 1 (Monitor Pipeline)
touch system.log
tail -f system.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.log

### Terminal 2 (Log Event Trigger)
echo "INFO: Initialization complete" >> system.log
echo "ERROR: Database connection timed out" >> system.log