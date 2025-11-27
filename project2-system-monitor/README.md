# 🖥️ Automated System Monitoring Shell Script

A comprehensive system monitoring solution that tracks CPU, memory, and disk usage with intelligent alerting and logging capabilities.

## ✨ Features

- **Real-time System Monitoring**: Track CPU, memory, disk usage, and active processes
- **Intelligent Alerting**: Configurable thresholds with automatic alert generation
- **Persistent Logging**: Timestamped logs with rotation and management
- **Interactive Interface**: User-friendly menu system for easy navigation
- **Continuous Monitoring**: Background monitoring with customizable intervals
- **Configuration Management**: Save and load monitoring preferences

## 🚀 Quick Start

```bash
# Make executable
chmod +x system_monitor.sh

# Run interactive mode
./system_monitor.sh

# Run continuous monitoring
./system_monitor.sh --monitor
```

## 📋 Menu Options

1. **View System Status** - Display current system metrics
2. **Set Alert Thresholds** - Configure CPU/Memory/Disk warning levels
3. **View Logs** - Show recent system activity and alerts
4. **Clear Logs** - Remove all log entries
5. **Start Continuous Monitoring** - Begin automated monitoring loop
6. **Exit** - Quit the application

## ⚙️ Configuration

Default thresholds:
- CPU Usage: 80%
- Memory Usage: 85%
- Disk Usage: 90%

Configuration is automatically saved to `monitor_config.conf`

## 📊 Sample Output

```
=== System Status ===
CPU Usage: 45.2%
Memory Usage: 67.8%
Disk Usage: 23%
Active Processes: 142
Load Average: 0.85, 0.92, 1.05
====================
```

## 🔧 Technical Implementation

- **Shell Scripting**: Pure Bash implementation
- **System Utilities**: Leverages `top`, `free`, `df`, `ps`
- **Error Handling**: Robust input validation and graceful error recovery
- **Logging**: Timestamped entries with automatic file management
- **Process Management**: Efficient resource monitoring with minimal overhead

## 📁 Files

- `system_monitor.sh` - Main monitoring script
- `monitor_config.conf` - Configuration file (auto-generated)
- `system_monitor.log` - Log file (auto-generated)

## 🎯 Learning Objectives Demonstrated

- ✅ Advanced shell scripting techniques
- ✅ Process management and system monitoring
- ✅ File I/O and redirection
- ✅ Conditional logic and loops
- ✅ Error handling and validation
- ✅ User interface design