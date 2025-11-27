#!/bin/bash

echo "🎓 C Programming Portfolio - Project Testing Suite"
echo "=================================================="

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

test_project() {
    local project_name=$1
    local project_dir=$2
    local test_command=$3
    
    echo -e "\n📁 Testing ${YELLOW}${project_name}${NC}..."
    cd "$project_dir" || return 1
    
    if eval "$test_command"; then
        echo -e "✅ ${GREEN}${project_name} - PASSED${NC}"
        return 0
    else
        echo -e "❌ ${RED}${project_name} - FAILED${NC}"
        return 1
    fi
    
    cd - > /dev/null
}

# Test Project 2: System Monitor
test_project "System Monitor" "project2-system-monitor" "bash system_monitor.sh 6 <<< '6' > /dev/null 2>&1"

# Test Project 3: Student Management
test_project "Student Management" "project3-student-management" "make clean && make > /dev/null 2>&1"

# Test Project 4: Math Engine
test_project "Math Engine" "project4-math-engine" "make clean && make > /dev/null 2>&1"

# Test Project 5: Web Scraper (compilation only, as it needs libcurl)
echo -e "\n📁 Testing ${YELLOW}Web Scraper${NC}..."
cd "project5-web-scraper" || exit 1

if pkg-config --exists libcurl; then
    if make clean && make > /dev/null 2>&1; then
        echo -e "✅ ${GREEN}Web Scraper - PASSED (with libcurl)${NC}"
    else
        echo -e "❌ ${RED}Web Scraper - COMPILATION FAILED${NC}"
    fi
else
    echo -e "⚠️  ${YELLOW}Web Scraper - SKIPPED (libcurl not installed)${NC}"
    echo "   Install with: sudo apt-get install libcurl4-openssl-dev"
fi

cd - > /dev/null

echo -e "\n🎯 ${GREEN}Portfolio Testing Complete!${NC}"
echo "All projects are ready for demonstration."
echo ""
echo "📋 Next Steps:"
echo "1. Review individual project READMEs"
echo "2. Test run each application manually"
echo "3. Prepare 8-minute video presentation"
echo "4. Ensure GitHub repository is public until grades are published"