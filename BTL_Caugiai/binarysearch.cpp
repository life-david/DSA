#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono> // Thu vien do thoi gian
#include <windows.h> // Thu vien lay thong tin bo nho
#include <psapi.h>   // Thu vien ho tro lay thong tin bo nho

using namespace std;
using namespace chrono;

struct Student {
    string id;
    string name;
    string clas;
    double gpa;
};

// So sanh 2 sinh vien theo ma sinh vien (dung cho sort va binary search)
bool compareByID(const Student& a, const Student& b) {
    return a.id < b.id;
}

// Ham so sanh chi dua tren ma sinh vien (cho binary search)
bool compareByIDOnly(const Student& a, const string& id) {
    return a.id < id;
}

// In thong tin sinh vien
void printStudent(const Student& s) {
    cout << "Ma sinh vien: " << s.id << endl;
    cout << "Ho ten     : " << s.name << endl;
    cout << "Lop        : " << s.clas << endl;
    cout << "Diem TB    : " << s.gpa << endl;
}

// Ham tach chuoi CSV thanh cac phan tu
vector<string> split(const string& line, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    string filePath = "data.csv"; // Duong dan toi file CSV
    string studentCode;          // Ma sinh vien can tim

    // Bat dau do thoi gian
    auto start = high_resolution_clock::now();

    // Nhap ma sinh vien tu nguoi dung
    cout << "Nhap ma sinh vien can tim: ";
    cin >> studentCode;

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Khong the mo file: " << filePath << endl;
        return 1;
    }

    vector<Student> students;
    string line;

    // Doc dong dau tien (header)
    getline(file, line);

    // Doc tung dong du lieu va luu vao danh sach sinh vien
    while (getline(file, line)) {
        vector<string> columns = split(line, ',');
        if (columns.size() >= 8) { // Dam bao du cot du lieu
            Student s;
            s.id = columns[2]; // Cot thu 3 la ma sinh vien
            s.name = columns[1];
            s.clas = columns[0];
            s.gpa = stod(columns[7]); // Cot thu 8 la diem trung binh
            students.push_back(s);
        }
    }

    file.close();

    // Sap xep danh sach sinh vien theo ma sinh vien
    sort(students.begin(), students.end(), compareByID);

    // Su dung binary search de tim sinh vien
    auto it = lower_bound(students.begin(), students.end(), studentCode, compareByIDOnly);

    if (it != students.end() && it->id == studentCode) {
        cout << "Sinh vien tim thay: " << endl;
        printStudent(*it);
    } else {
        cout << "Khong tim thay sinh vien voi ma: " << studentCode << endl;
    }

    // Ket thuc do thoi gian
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();

    // Lay thong tin bo nho
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        size_t memoryUsageKB = memInfo.WorkingSetSize / 1024;
        cout << "Dung luong bo nho su dung: " << memoryUsageKB << " KB" << endl;
    } else {
        cerr << "Khong the lay thong tin bo nho." << endl;
    }

    // Hien thi thoi gian chay chuong trinh
    cout << "Thoi gian chay chuong trinh: " << duration << " nanoseconds" << endl;

    return 0;
}
