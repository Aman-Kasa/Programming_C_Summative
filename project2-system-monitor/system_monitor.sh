#!/bin/bash

# System Monitor Script
# Author: Student
# Description: Automated system monitoring with alerts and logging

LOG_FILE="system_monitor.log"
CONFIG_FILE="monitor_config.conf"

# Default thresholds
CPU_THRESHOLD=80
MEMORY_THRESHOLD=85
DISK_THRESHOLD=90

# Load configuration if exists
load_config() {
    if [[ -f "$CONFIG_FILE" ]]; then
        source "$CONFIG_FILE"
    fi
}

# Save configuration
save_config() {
    cat > "$CONFIG_FILE" << EOF
CPU_THRESHOLD=$CPU_THRESHOLD
MEMORY_THRESHOLD=$MEMORY_THRESHOLD
DISK_THRESHOLD=$DISK_THRESHOLD
EOF
}

# Log with timestamp
log_message() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a "$LOG_FILE"
}

# Get system metrics
get_cpu_usage() {
    top -bn1 | grep "Cpu(s)" | awk '{print $2}' | sed 's/%us,//'
}

get_memory_usage() {
    free | grep Mem | awk '{printf "%.1f", ($3/$2) * 100.0}'
}

get_disk_usage() {
    df -h / | awk 'NR==2 {print $5}' | sed 's/%//'
}

# Check thresholds and alert
check_alerts() {
    local cpu=$(get_cpu_usage)
    local memory=$(get_memory_usage)
    local disk=$(get_disk_usage)
    
    cpu_int=${cpu%.*}
    memory_int=${memory%.*}
    
    if (( cpu_int > CPU_THRESHOLD )); then
        log_message "ALERT: CPU usage ${cpu}% exceeds threshold ${CPU_THRESHOLD}%"
    fi
    
    if (( memory_int > MEMORY_THRESHOLD )); then
        log_message "ALERT: Memory usage ${memory}% exceeds threshold ${MEMORY_THRESHOLD}%"
    fi
    
    if (( disk > DISK_THRESHOLD )); then
        log_message "ALERT: Disk usage ${disk}% exceeds threshold ${DISK_THRESHOLD}%"
    fi
}

# Display system status
show_status() {
    echo "=== System Status ==="
    echo "CPU Usage: $(get_cpu_usage)%"
    echo "Memory Usage: $(get_memory_usage)%"
    echo "Disk Usage: $(get_disk_usage)%"
    echo "Active Processes: $(ps aux | wc -l)"
    echo "Load Average: $(uptime | awk -F'load average:' '{print $2}')"
    echo "===================="
}

# Set thresholds
set_thresholds() {
    echo "Current thresholds:"
    echo "CPU: $CPU_THRESHOLD%"
    echo "Memory: $MEMORY_THRESHOLD%"
    echo "Disk: $DISK_THRESHOLD%"
    echo
    
    read -p "Enter new CPU threshold (0-100): " new_cpu
    read -p "Enter new Memory threshold (0-100): " new_mem
    read -p "Enter new Disk threshold (0-100): " new_disk
    
    if [[ $new_cpu =~ ^[0-9]+$ ]] && (( new_cpu >= 0 && new_cpu <= 100 )); then
        CPU_THRESHOLD=$new_cpu
    fi
    
    if [[ $new_mem =~ ^[0-9]+$ ]] && (( new_mem >= 0 && new_mem <= 100 )); then
        MEMORY_THRESHOLD=$new_mem
    fi
    
    if [[ $new_disk =~ ^[0-9]+$ ]] && (( new_disk >= 0 && new_disk <= 100 )); then
        DISK_THRESHOLD=$new_disk
    fi
    
    save_config
    echo "Thresholds updated successfully!"
}

# View logs
view_logs() {
    if [[ -f "$LOG_FILE" ]]; then
        echo "=== Recent Logs ==="
        tail -20 "$LOG_FILE"
    else
        echo "No logs found."
    fi
}

# Clear logs
clear_logs() {
    read -p "Are you sure you want to clear all logs? (y/N): " confirm
    if [[ $confirm =~ ^[Yy]$ ]]; then
        > "$LOG_FILE"
        echo "Logs cleared."
    fi
}

# Monitoring loop
start_monitoring() {
    echo "Starting continuous monitoring... Press Ctrl+C to stop"
    while true; do
        show_status
        check_alerts
        sleep 60
    done
}

# Main menu
show_menu() {
    echo
    echo "=== System Monitor ==="
    echo "1. View system status"
    echo "2. Set alert thresholds"
    echo "3. View logs"
    echo "4. Clear logs"
    echo "5. Start continuous monitoring"
    echo "6. Exit"
    echo "======================"
    read -p "Choose an option: " choice
}

# Main execution
load_config

if [[ $# -eq 1 && $1 == "--monitor" ]]; then
    start_monitoring
else
    while true; do
        show_menu
        case $choice in
            1) show_status ;;
            2) set_thresholds ;;
            3) view_logs ;;
            4) clear_logs ;;
            5) start_monitoring ;;
            6) echo "Goodbye!"; exit 0 ;;
            *) echo "Invalid option. Please try again." ;;
        esac
    done
fi