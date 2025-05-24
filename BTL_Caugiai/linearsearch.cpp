#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>

// Cấu trúc dữ liệu cho sinh viên
struct Student {
    int id;
    std::string fullName;
    std::string studentId;
    double attendance;
    double midtermScore;
    double projectScore;
    double finalScore;
    double averageScore;
};

// Hàm so sánh hai sinh viên theo mã sinh viên
bool compareStudentById(const Student& a, const Student& b) {
    return a.studentId < b.studentId;
}

// Hàm tìm kiếm nhị phân
int binarySearch(const std::vector<Student>& students, const std::string& targetId) {
    int left = 0;
    int right = students.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (students[mid].studentId == targetId) {
            return mid;
        }

        if (students[mid].studentId < targetId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Không tìm thấy
}

// Hàm đọc dữ liệu từ file CSV
std::vector<Student> readStudentsFromCSV(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return students;
    }

    std::string line;
    // Bỏ qua dòng tiêu đề
    std::getline(file, line);

    while (std::getline(file, line)) {
        Student student;
        size_t pos = 0;
        size_t nextPos;

        // Đọc STT
        nextPos = line.find(",", pos);
        student.id = std::stoi(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // Đọc họ và tên
        nextPos = line.find(",", pos);
        student.fullName = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        // Đọc mã sinh viên
        nextPos = line.find(",", pos);
        student.studentId = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        // Đọc điểm chuyên cần
        nextPos = line.find(",", pos);
        student.attendance = std::stod(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // Đọc điểm kiểm tra giữa kỳ
        nextPos = line.find(",", pos);
        student.midtermScore = std::stod(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // Đọc điểm bài tập lớn
        nextPos = line.find(",", pos);
        student.projectScore = std::stod(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // Đọc điểm kiểm tra cuối kỳ
        nextPos = line.find(",", pos);
        student.finalScore = std::stod(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // Đọc điểm trung bình môn
        student.averageScore = std::stod(line.substr(pos));

        students.push_back(student);
    }

    file.close();
    return students;
}

int main() {
    // Đọc dữ liệu sinh viên từ file CSV
    std::vector<Student> students = readStudentsFromCSV("data.csv");

    // Sắp xếp sinh viên theo mã sinh viên
    std::sort(students.begin(), students.end(), compareStudentById);

    // Nhập mã sinh viên cần tìm
    std::string targetId;
    std::cout << "Enter student ID to search: ";
    std::cin >> targetId;

    // Lặp lại tìm kiếm nhiều lần để đo thời gian trung bình
    const int iterations = 1000; // Số lần lặp
    auto totalDuration = std::chrono::nanoseconds(0);
    int result = -1; // Khởi tạo result ngoài vòng lặp

    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        result = binarySearch(students, targetId);
        auto endTime = std::chrono::high_resolution_clock::now();
        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    }

    double averageDuration = totalDuration.count() / static_cast<double>(iterations);
    std::cout << "\nAverage search time: " << averageDuration << " nanoseconds" << std::endl;

    // Hiển thị kết quả tìm kiếm (lần cuối cùng)
    if (result != -1) {
        std::cout << "\nStudent found!" << std::endl;
        std::cout << "Full name: " << students[result].fullName << std::endl;
        std::cout << "Student ID: " << students[result].studentId << std::endl;
        std::cout << "Attendance: " << students[result].attendance << std::endl;
        std::cout << "Midterm score: " << students[result].midtermScore << std::endl;
        std::cout << "Project score: " << students[result].projectScore << std::endl;
        std::cout << "Final score: " << students[result].finalScore << std::endl;
        std::cout << "Average score: " << students[result].averageScore << std::endl;
    } else {
        std::cout << "\nStudent with ID " << targetId << " not found." << std::endl;
    }

    // Tính và hiển thị dung lượng chiếm
    size_t memoryUsage = sizeof(Student) * students.size() + sizeof(students);
    std::cout << "Memory usage: " << memoryUsage << " bytes" << std::endl;

    return 0;
}