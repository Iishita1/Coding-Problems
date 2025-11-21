// Application Abuse (100% Acceptance)
// Time limit: 1000 ms Memory limit: 256 MB
// Warm greetings to all IEEExtreme Participants from the Xplore API Team!
// As part of the IEEExtreme Competition, you will face a programming challenge where you'll need to analyze web application logs to identify potential instances of application misuse.
// For a full dynamic database search IEEE Xplore API is available for your IEEE research needs. Xplore API provides metadata on 4.9mm academic works and is now delivering full-text content on 50k 'Open Access' articles. Xplore API will make your research needs fast and easy. The Xplore API Portal supports PHP, Python and Java as well as providing output in JSON and XML formats. Many API use cases are listed within the API Portal.
// Xplore API registration is free. To learn more about IEEE Xplore API please visit developer.ieee.org/ and register for an API key TODAY!
// Challenge
// Users log into the IEEE document repository application to search for articles, download PDFs, view abstracts, and perform various other tasks. To access the application, users must agree to the acceptable usage terms. Your task is to identify users who are violating these terms.
// Standard input
// The input consists of three parts: a web log descriptor, rules of abuse, and web log entries. The first row outlines the rules of abuse, which detail five potential ways individuals can misuse the system:
// 1. Using X or more different user agents in a single day, indicated by agent=X.
// 2. Using X or more different IP addresses in a single day, indicated by ip=x.
// 3. Downloading PDFs at least X times, indicated by pdf=X.
// 4. Initiating X or more sessions, indicated by session=X.
// 5. Engaging in X or more crawling activities in a single day, indicated by crawl=X.
// The settings can be listed in any order. For example:
// 1. agent-3, ip-4, pdf-10, session=20, crawl-30.
// 2. session-20, pdf-100.
// Not every situation requires a comprehensive set of rules. For example, you may only need to check for the existence of session and pdf abuse, without the need for additional rules.
// To determine if an individual is using a robot to download PDFs sequentially, examine the order of the PDF downloads. For example, if the user downloads the PDFs in the following order: 1.pdf, 2.pdf, 3.pdf, ..., 10.pdf, this indicates they are likely using a robot. There can be other page requests in between PDF requests. For example: 1.pdf, /search/criteria, 2.pdf, /search/results,..., 10.pdf. This is still considered abuse.
// If the user downloads more than the specified number of PDFs sequentially (set by the parameter crawl=X), report this in the output. The downloads must be in sequential order by date and time to be considered part of the same robot-driven download session.
// For instance, if the user downloads the PDFs in the order 1.pdf, 4.pdf, 2.pdf, 3.pdf, this is not considered sequential and would not reach the limit of crawl=4 downloads sequentially, even though x=4 PDFs were downloaded.
// Keep track of the ids and check if the number of sessions for each id is equal to or greater than a specified setting. For instance, if a certain individual has 10 sessions and the setting is set to session=5, then in the output, print {Id} session=10.
// When considering the rules, remember that the settings are based on a daily timeframe. So, if the log entries cover multiple days, you may not identify any abuse when looking at individual days, even though there might be abuse when considering the entire set of log entries.
// The second row contains the log file descriptor. The log file contains the following fields:
// 1. Host - Domain name. For example, documents.ieee.org.
// 2. Client IP - IP address of the client that is making a request to the server.
// 3. Id - Unique string identifying the individual.
// 4. Date - Date of the request. The format will be [dd/Mmm/YYYY:HH24:mm:ss]. Example: [07/Oct/2025:14:26:41].
// 5. Request - The URL requested. For example: "GET /article/abstract?id=XYZ HTTP/1.1"
// 6. HTTP Status - Standard list of HTTP Status codes. See Wikipedia - List of HTTP status codes.
// 7. User Agent - A string of text that identifies the client software originating a request.
// 8. Session Cookie - A string used to track a user's interactions during a single session.
// All fields will be present. However, the order is not always the same. Examples:
// 1. Host, Client IP, Id, Date, Request, HTTP Status, User Agent, Session Cookie 2. Host, Client IP, Date, Request, HTTP Status, User Agent, Session Cookie, Id
// The remaining rows will be the log entries. If a field has no value, it will be set to a dash
// 1. documents.ieee.org 131.155.125.139 XYZ [07/Feb/2024:12:26:41] "GET /document/abstract?id=123 HTTP/1.1" 200 "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36" "ABC123"
// 2. documents.ieee.org 121.135.110.122 - [18/Mar/2025:18:20:33] "GET /document/123.pdf HTTP/1.1" 200 "Mozilla/5.0 (Windows Mobile 10; Android 10.0; Microsoft; Lumia 950XL) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.0.0 Mobile Safari/537.36 Edge/40.15254.603" "456LLL"
// The Date will always be enclosed by square brackets and the User Agent, Request and Session Cookie will always be enclosed by double quotes. Lastly any HTTP Status code other than 200 should be ignored and not counted towards a violation.
// Standard output
// Constraints and notes
// ⚫ Number of records < 10,000.
// • A request for a PDF download will always take the form "GET /document/{XXX}.pdf HTTP/1.1" where (XXX) is a string containing numbers only.
// • Valid log entries are in date order.
// • If there are no ids that have abuse simple print N/A in the output.
// • There will not be duplicate abuse of the same type for the same id over multiple days. For instance, if the pdf abuse is set as 10 and there are two days contained in the file, you will never have the case XYZ pdf-11 for 01/01/2025 and XYZ pdf-12 for 01/02/2025.
// Input
// agent-2, ip-2, pdf-2, session=2, crawl Host, Client IP, Id, Date, Request, HT documents.ieee.org 116.84.105.37 ABCAB documents.ieee.org 116.84.105.37 ABCAB documents.ieee.org 116.84.105.37 FVNYKI documents.ieee.org 188.155.4.245 documents.ieee.org 38.206.21.104 PKTJV documents.ieee.org 93.30.209.202
// -
// [01
// -
// [01
// [01/
// documents.ieee.org 111.116.84.105.37 F documents.ieee.org 4.236.187.49 documents.ieee.org 58.109.163.186 - [0
// -
// [01
// documents.ieee.org 103.37.68.141 documents.ieee.org 98.209.252.152 HTRX documents.ieee.org 188.155.4.245
// -
// [01
// documents.ieee.org 98.209.252.152 HTRX
// Output
// ABCABC agent=2 ABCABC pdf=2 FVNYKW agent=2 FVNYKW ip=2 FVNYKW pdf=2
// FVNYKW session=2
// HTRXVC pdf=2
// Explanation
// The queries go as follows:
// Query 1 - Valid.
// • Id: ABCABC
// • Date: 01/Oct/2025
// • Request: 779.pdf
// . User Agent: "Mozilla/5.0 (Linux;
// Android 10; ELS-NX9)
// AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Mobile Safari/537.36
// OPR/58.2.2878.53403"
// • Session Cookie: "JKXC1Xx22zMrHRxx"
// ·
// ·
// lp: "JKXC1Xx22zMrHRxx"
// Query 2 - Valid.
// • Id: ABCABC
// • Date: 01/Oct/2025
// .
// .
// • Request: 780.pdf
// . User Agent: "11 Mozilla/5.0 (Linux;
// Android 10; ELS-NX9)
// AppleWebKit/537.36 (KHTML, like
// Gecko) Chrome/81.0.4044.138 Mobile Safari/537.36
// OPR/58.2.2878.53403"
// Session Cookie: "JKXC1Xx22zMrHRxx"
// .
// Ip: "JKXc1Xx22zMrHRxx"
// Query 3 - Valid.
// • Id: FVNYKW
// • Date: 01/Oct/2025
// • Request: 779.pdf
// .
// • User Agent: "Mozilla/5.0 (Linux;
// Android 10; ELS-NX9)
// AppleWebKit/537.36 (KHTML, like
// Gecko) Chrome/81.0.4044.138 Mobile Safari/537.36
// OPR/58.2.2878.53403"
// Session Cookie: "JKXclXx22zMrHR"
// • Ip: "JKXclxx22zMrHR"
// Query 4 - Invalid. No Id
// Query 5 - Valid.
// • Id: PKTJVG
// • Date: 01/Oct/2025
// • Request: non-pdf
// .
// • User Agent: "Mozilla/5.0 (Linux; arm; Android 7.1.1; SM-J510FN) AppleWebKit/537.36 (KHTML, like
// Gecko) Chrome/79.0.3945.136
// YaBrowser/20.2.5.120.00 Mobile SA/1 Safari/537.36"
// • Session Cookie: "#yHigR#edHOWA*"
// • Ip: "#yHigR#edHOWA*"
// .
// Query 6 - Invalid. No Id
// Query 7 - Valid.
// • Id: FVNYKW
// • Date: 01/Oct/2025
// • Request: 714.pdf
// .
// • User Agent: "1111 Mozilla/5.0
// (Linux; Android 10; ELS-NX9)
// AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Mobile Safari/537.36
// OPR/58.2.2878.53403"
// Query 7 - Valid.
// • Id: FVNYKW
// • Date: 01/Oct/2025
// • Request: 714.pdf
// • User Agent: "1111 Mozilla/5.0
// ·
// .
// (Linux; Android 10; ELS-NX9) AppleWebKit/537.36 (KHTML, like
// Gecko) Chrome/81.0.4044.138 Mobile Safari/537.36
// OPR/58.2.2878.53403"
// Session Cookie: "111
// JKXclXx22zMrHR"
// lp: "111 JKXclXx22zMrHR"
// Query 8 - Invalid. No Id
// Query 9 - Invalid. No Id
// Query 10 - Invalid. No Id
// Query 11 - Valid.
// • Id: HTRXVC
// • Date: 01/Oct/2025
// • Request: 622.pdf
// • User Agent: "Mozilla/5.0 (Windows NT 6.3;) AppleWebKit/537.36 (KHTML, like Gecko)
// Chrome/81.0.4044.138
// YaBrowser/20.6.1.151 Yowser/2.5
// Yptp/1.23 Safari/537.36"
// . Session Cookie: "5vnkAHpJx0W04D"
// • Ip: "5vnkAHpJx0W04D"
// Query 12 - Invalid. No Id
// Query 13 - Valid.
// • Id: HTRXVC
// • Date: 01/Oct/2025
// .
// • Request: 625.pdf
// . User Agent: "Mozilla/5.0 (Windows
// NT 6.3;) AppleWebKit/537.36
// (KHTML, like Gecko) Chrome/81.0.4044.138
// YaBrowser/20.6.1.151 Yowser/2.5
// Yptp/1.23 Safari/537.36"
// • Session Cookie: "5vnkAHpJx0W04D" • Ip: "5vnkAHpJx0W04D"
// the final abuse contains:
// • ABCABC agent=2, since it has 2 different agents on day 01/Oct/2025 (Requests 1 and 2).
// • ABCABC pdf=2, since it has
// downloaded the pdf files 779.pdf and 780.pdf on day 01/Oct/2025
// (Requests 1 and 2).
// • FVNYKW agent-2, since since it has 2 different agents on day 01/Oct/2025 (Requests 3 and 7).
// • FVNYKW ip=2, since it has 2 different ips on day 01/Oct/2025 (Requests 3 and 7).
// • FVNYKW pdf=2, since it has
// downloaded the pdf files 779.pdf and 714.pdf on day 01/Oct/2025
// (Requests 3 and 7).
// • FVNYKW session=2, since it has used 2 different session cookies on day 01/Oct/2025 (Requests 3 and 7).
// • HTRXVC pdf=2, since it has
// downloaded the pdf files 622.pdf and 625.pdf on day 01/Oct/2025 (Requests 11 and 13).
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct LogEntry {
    string host, clientIP, id, date, request, httpStatus, userAgent, sessionCookie;
    int pdfNum = -1;
    string day;
}; 

unordered_map<string, int> parseRules(const string& line) {
    unordered_map<string, int> rules;
    size_t pos = 0;
    
    while (pos < line.length()) {
        size_t eq = line.find('=', pos);
        if (eq == string::npos) break;
        
        size_t start = pos;
        while (start < eq && (line[start] == ' ' || line[start] == '\t' || line[start] == ',')) start++;
        size_t end = eq;
        while (end > start && (line[end-1] == ' ' || line[end-1] == '\t')) end--;
        
        string key = line.substr(start, end - start);
        
        size_t numStart = eq + 1;
        size_t numEnd = line.find(',', numStart);
        if (numEnd == string::npos) numEnd = line.length();
        
        int val = stoi(line.substr(numStart, numEnd - numStart));
        rules[key] = val;
        
        pos = numEnd + 1;
    }
    return rules;
}

string extractQuoted(const string& s, size_t& pos) {
    size_t start = s.find('"', pos);
    if (start == string::npos) return "-";
    size_t end = s.find('"', start + 1);
    pos = end + 1;
    return s.substr(start + 1, end - start - 1);
}

string extractBracketed(const string& s, size_t& pos) {
    size_t start = s.find('[', pos);
    if (start == string::npos) return "";
    size_t end = s.find(']', start + 1);
    pos = end + 1;
    return s.substr(start + 1, end - start - 1);
}

string getDay(const string& date) {
    return date.substr(0, 11); // "dd/Mmm/YYYY"
}

int extractPdfNumber(const string& request) {
    size_t pdfPos = request.find(".pdf");
    if (pdfPos == string::npos) return -1;
    
    size_t start = pdfPos;
    while (start > 0 && isdigit(request[start - 1])) start--;
    
    if (start < pdfPos) {
        return stoi(request.substr(start, pdfPos - start));
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    
    // First line: rules
    getline(cin, line);
    auto rules = parseRules(line);
    
    // Second line: descriptor
    getline(cin, line);
    vector<string> fields;
    stringstream ss(line);
    string field;
    while (getline(ss, field, ',')) {
        field.erase(0, field.find_first_not_of(" \t"));
        field.erase(field.find_last_not_of(" \t") + 1);
        fields.push_back(field);
    }
    
    vector<LogEntry> logs;
    logs.reserve(10000); // Pre-allocate max size
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        LogEntry entry;
        
        // Parse line by splitting on spaces but respecting quotes and brackets
        vector<string> parts;
        parts.reserve(8); // Typical log has 8 fields
        size_t i = 0;
        while (i < line.length()) {
            while (i < line.length() && isspace(line[i])) i++;
            if (i >= line.length()) break;
            
            if (line[i] == '[') {
                size_t end = line.find(']', i);
                parts.push_back(line.substr(i + 1, end - i - 1));
                i = end + 1;
            } else if (line[i] == '"') {
                size_t end = line.find('"', i + 1);
                parts.push_back(line.substr(i + 1, end - i - 1));
                i = end + 1;
            } else {
                size_t end = i;
                while (end < line.length() && !isspace(line[end]) && line[end] != '[' && line[end] != '"') end++;
                parts.push_back(line.substr(i, end - i));
                i = end;
            }
        }
        
        // Map parts to fields
        int partIdx = 0;
        for (const auto& f : fields) {
            if (partIdx >= parts.size()) break;
            
            if (f == "Host") entry.host = parts[partIdx++];
            else if (f == "Client IP") entry.clientIP = parts[partIdx++];
            else if (f == "Id") entry.id = parts[partIdx++];
            else if (f == "Date") {
                entry.date = parts[partIdx++];
                entry.day = getDay(entry.date);
            }
            else if (f == "Request") {
                entry.request = parts[partIdx++];
                entry.pdfNum = extractPdfNumber(entry.request);
            }
            else if (f == "HTTP Status") entry.httpStatus = parts[partIdx++];
            else if (f == "User Agent") entry.userAgent = parts[partIdx++];
            else if (f == "Session Cookie") entry.sessionCookie = parts[partIdx++];
        }
        
        if (entry.httpStatus == "200" && entry.id != "-" && !entry.id.empty()) {
            logs.push_back(entry);
        }
    }
    
    // Track violations per id per day
    unordered_map<string, unordered_map<string, unordered_set<string>>> agentsByDay;
    unordered_map<string, unordered_map<string, unordered_set<string>>> ipsByDay;
    unordered_map<string, unordered_map<string, int>> pdfsByDay;
    unordered_map<string, unordered_map<string, unordered_set<string>>> sessionsByDay;
    unordered_map<string, unordered_map<string, vector<int>>> pdfSequenceByDay;
    
    for (const auto& log : logs) {
        const string& id = log.id;
        const string& day = log.day;
        agentsByDay[id][day].insert(log.userAgent);
        ipsByDay[id][day].insert(log.clientIP);
        sessionsByDay[id][day].insert(log.sessionCookie);
        
        if (log.pdfNum != -1) {
            pdfsByDay[id][day]++;
            pdfSequenceByDay[id][day].push_back(log.pdfNum);
        }
    }
    
    unordered_map<string, vector<pair<string, int>>> violations;
    
    for (const auto& [id, dayData] : agentsByDay) {
        for (const auto& [day, agents] : dayData) {
            if (rules.count("agent") && agents.size() >= rules["agent"]) {
                violations[id].push_back({"agent", agents.size()});
            }
        }
    }
    
    for (const auto& [id, dayData] : ipsByDay) {
        for (const auto& [day, ips] : dayData) {
            if (rules.count("ip") && ips.size() >= rules["ip"]) {
                violations[id].push_back({"ip", ips.size()});
            }
        }
    }
    
    for (const auto& [id, dayData] : pdfsByDay) {
        for (const auto& [day, count] : dayData) {
            if (rules.count("pdf") && count >= rules["pdf"]) {
                violations[id].push_back({"pdf", count});
            }
        }
    }
    
    for (const auto& [id, dayData] : sessionsByDay) {
        for (const auto& [day, sessions] : dayData) {
            if (rules.count("session") && sessions.size() >= rules["session"]) {
                violations[id].push_back({"session", sessions.size()});
            }
        }
    }
    
    // Check crawl violations
    if (rules.count("crawl")) {
        for (const auto& [id, dayData] : pdfSequenceByDay) {
            for (const auto& [day, pdfs] : dayData) {
                int maxSeq = 1, curSeq = 1;
                for (int i = 1; i < pdfs.size(); i++) {
                    if (pdfs[i] == pdfs[i-1] + 1) {
                        curSeq++;
                        maxSeq = max(maxSeq, curSeq);
                    } else {
                        curSeq = 1;
                    }
                }
                if (maxSeq >= rules["crawl"]) {
                    violations[id].push_back({"crawl", maxSeq});
                }
            }
        }
    }
    
    if (violations.empty()) {
        cout << "N/A\n";
    } else {
        // Sort IDs
        vector<string> ids;
        ids.reserve(violations.size());
        for (const auto& [id, _] : violations) ids.emplace_back(id);
        sort(ids.begin(), ids.end());
        
        for (const auto& id : ids) {
            auto& viols = violations[id];
            sort(viols.begin(), viols.end());
            for (const auto& [type, val] : viols) {
                cout << id << " " << type << "=" << val << "\n";
            }
        }
    }
    
    return 0;
}
