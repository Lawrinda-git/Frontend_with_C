#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void url_decode(char *dest, const char *src) {
    while (*src) {
        if (*src == '%') {
            int value;
            sscanf(src + 1, "%2x", &value);
            *dest++ = (char)value;
            src += 3; 
        } else if (*src == '+') {
            *dest++ = ' '; // Convert '+' to space
            src++;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0'; // Null-terminate the destination string
}

char determine_grade(int marks) {
    if (marks >= 80) return 'A';
    else if (marks >= 65) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 55) return 'D';
    else if (marks >= 45) return 'E';
    else return 'F';
}

void parse_query_string(char *query, char *name, char *student_number, char *programme, char *year, char *semester, char *course1, char *course2, char *course3, char *course4, char *course5, int *sub1, int *sub2, int *sub3, int *sub4, int *sub5) {
    char *token = strtok(query, "&");
    while (token != NULL) {
        if (sscanf(token, "studentName=%[^&]", name) == 1) {}
        else if (sscanf(token, "studentNumber=%[^&]", student_number) == 1) {}
        else if (sscanf(token, "programme=%[^&]", programme) == 1) {}
        else if (sscanf(token, "year=%[^&]", year) == 1) {}
        else if (sscanf(token, "semester=%[^&]", semester) == 1) {}
        else if (sscanf(token, "course1=%[^&]", course1) == 1) {}
        else if (sscanf(token, "course2=%[^&]", course2) == 1) {}
        else if (sscanf(token, "course3=%[^&]", course3) == 1) {}
        else if (sscanf(token, "course4=%[^&]", course4) == 1) {}
        else if (sscanf(token, "course5=%[^&]", course5) == 1) {}
        else if (sscanf(token, "sub1=%d", sub1) == 1) {}
        else if (sscanf(token, "sub2=%d", sub2) == 1) {}
        else if (sscanf(token, "sub3=%d", sub3) == 1) {}
        else if (sscanf(token, "sub4=%d", sub4) == 1) {}
        else if (sscanf(token, "sub5=%d", sub5) == 1) {}
        token = strtok(NULL, "&");
    }
}

void print_result(const char *name, const char *student_number, const char *programme, const char *year, const char *semester, const char *course1, int sub1, const char *course2, int sub2, const char *course3, int sub3, const char *course4, int sub4, const char *course5, int sub5, float total_marks) {
    float weights[5] = {3.0, 3.0, 2.0, 1.0, 1.0};
    float total_weight = 0;
    float weighted_sum = 0;

    int marks[5] = {sub1, sub2, sub3, sub4, sub5};
    
    for (int i = 0; i < 5; i++) {
        weighted_sum += marks[i] * weights[i];
        total_weight += weights[i];
    }

    float cwa = weighted_sum / total_weight;
    int sum = sub1 + sub2 + sub3 + sub4 + sub5;
    float percentage = (sum / total_marks) * 100;

    // Display results with enhanced CSS
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Results</title>");
    printf("<style>");
    printf("body { font-family: Arial, sans-serif; background-color: #dae1e1; padding: 20px; }");
    printf("h1 { color: #333; text-align: center; }");
    printf(".result { background-color: #fff; border-radius: 8px; padding: 20px; box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1); max-width: 600px; margin: auto; }");
    printf("table { width: 100%%; border-collapse: collapse; margin-top: 20px; }");
    printf("th, td { padding: 10px; text-align: left; border: 1px solid #ccc; }");
    printf("th { background-color: #007BFF; color: white; }");
    printf("tr:nth-child(even) { background-color: #f2f2f2; }");
    printf(".pass { color: green; font-weight: bold; }");
    printf(".fail { color: red; font-weight: bold; }");
    printf("</style>");
    printf("</head><body>");
    printf("<div class='result'>");
    printf("<h1>HERTEACHING COMPLEX</h1>");
    printf("<h3>Name: <i>%s</i></h3>", name);
    printf("<h3>Student Number: <i>%s</i></h3>", student_number);
    printf("<h3>Programme: <i>%s</i></h3>", programme);
    printf("<h3>Year of Study: <i>%s</i></h3>", year);
    printf("<h3>Semester: <i>%s</i></h3>", semester);
    printf("<table><tr><th>Course</th><th>Marks</th><th>Grade</th></tr>");
    printf("<tr><td>%s</td><td>%d</td><td>%c</td></tr>", course1, sub1, determine_grade(sub1));
    printf("<tr><td>%s</td><td>%d</td><td>%c</td></tr>", course2, sub2, determine_grade(sub2));
    printf("<tr><td>%s</td><td>%d</td><td>%c</td></tr>", course3, sub3, determine_grade(sub3));
    printf("<tr><td>%s</td><td>%d</td><td>%c</td></tr>", course4, sub4, determine_grade(sub4));
    printf("<tr><td>%s</td><td>%d</td><td>%c</td></tr>", course5, sub5, determine_grade(sub5));
    printf("</table>");
    printf("<p>Total Marks: %d</p>", sum);
    printf("<p>Total Percentage: %.2f%%</p>", percentage);
    printf("<p>Cumulative Weighted Average (CWA): %.2f</p>", cwa);
    printf("<p class='%s'>%s</p>", (percentage >= 50) ? "pass" : "fail", 
        (percentage >= 50) ? "Congratulations, you passed!" : "Sorry, you failed.");
    printf("</div></body></html>");
}

int main(void) {
    char name[100] = "";
    char student_number[100] = "";
    char programme[100] = "";
    char year[10] = "";
    char semester[10] = "";
    char course1[100] = "", course2[100] = "", course3[100] = "", course4[100] = "", course5[100] = "";
    int sub1 = 0, sub2 = 0, sub3 = 0, sub4 = 0, sub5 = 0;
    float total_marks = 500.0;

    // Get the query string
    char *query_string = getenv("QUERY_STRING");
    if (query_string != NULL) {
        // Decode the query string before parsing
        char decoded_query[1024]; // Ensure this is large enough to hold the decoded string
        url_decode(decoded_query, query_string);
        
        parse_query_string(decoded_query, name, student_number, programme, year, semester, course1, course2, course3, course4, course5, &sub1, &sub2, &sub3, &sub4, &sub5);
        
        // Validate the marks
        if (sub1 < 0 || sub1 > 100 || sub2 < 0 || sub2 > 100 || 
            sub3 < 0 || sub3 > 100 || sub4 < 0 || sub4 > 100 || 
            sub5 < 0 || sub5 > 100) {
            printf("Content-Type: text/html\n\n");
            printf("<html><body><h1>Error: Marks must be between 0 and 100.</h1></body></html>");
            return 1;
        }

        print_result(name, student_number, programme, year, semester, course1, sub1, course2, sub2, course3, sub3, course4, sub4, course5, sub5, total_marks);
    } else {
        // If there's no input, show an error
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Error: No data submitted.</h1></body></html>");
    }

    return 0;
}
