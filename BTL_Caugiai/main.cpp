#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <windows.h>
#include <psapi.h>
#include <random>

using namespace std;
using namespace std::chrono;

// === Cấu trúc SinhVien ===
struct SinhVien {
    string msv;
    string hoTen;
    double diemTBM;

    friend ostream& operator<<(ostream& os, const SinhVien& sv) {
        os << sv.msv << "," << sv.hoTen << "," << fixed << setprecision(2) << sv.diemTBM;
        return os;
    }
};

// === Hàm đọc file CSV ===
vector<SinhVien> docFileCSV(const string& tenFile) {
    vector<SinhVien> danhSach;
    ifstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file: " << tenFile << endl;
        return danhSach;
    }

    string line;
    getline(file, line); // Bỏ qua dòng tiêu đề

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 8) continue; // Bỏ qua dòng thiếu dữ liệu

        SinhVien sv;
        sv.hoTen = tokens[1];
        sv.msv = tokens[2];
        try {
            sv.diemTBM = stod(tokens[7]);
        } catch (...) {
            sv.diemTBM = 0.0; // Nếu lỗi, gán 0
        }

        danhSach.push_back(sv);
    }

    file.close();
    return danhSach;
}

// === Hàm ghi file CSV ===
void ghiFileCSV(const vector<SinhVien>& danhSach, const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file de ghi: " << tenFile << endl;
        return;
    }

    file << "Ma Sinh Vien,Ho va Ten,TBM\n";
    for (const auto& sv : danhSach) {
        file << sv << "\n";
    }

    file.close();
}

// === Linear Search ===
void linearSearchMain() {
    vector<SinhVien> danhSach = docFileCSV("data.csv");
    if (danhSach.empty()) {
        cerr << "Khong co du lieu hop le trong file.\n";
        return;
    }

    string targetId;
    cout << "Nhap ma sinh vien can tim: ";
    cin >> targetId;

    auto start = high_resolution_clock::now();
    auto it = find_if(danhSach.begin(), danhSach.end(), [&targetId](const SinhVien& sv) {
        return sv.msv == targetId;
    });
    auto end = high_resolution_clock::now();

    if (it != danhSach.end()) {
        cout << "Sinh vien tim thay: " << *it << endl;
    } else {
        cout << "Khong tim thay sinh vien voi ma: " << targetId << endl;
    }

    size_t memoryUsage = sizeof(SinhVien) * danhSach.size() + sizeof(danhSach);
    cout << "Thoi gian tim kiem: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";
    cout << "Dung luong bo nho su dung: " << memoryUsage / 1024.0 << " KB\n";
}

// === Binary Search ===
void binarySearchMain() {
    vector<SinhVien> danhSach = docFileCSV("data.csv");
    if (danhSach.empty()) {
        cerr << "Khong co du lieu hop le trong file.\n";
        return;
    }

    sort(danhSach.begin(), danhSach.end(), [](const SinhVien& a, const SinhVien& b) {
        return a.msv < b.msv;
    });

    string targetId;
    cout << "Nhap ma sinh vien can tim: ";
    cin >> targetId;

    auto start = high_resolution_clock::now();
    auto it = lower_bound(danhSach.begin(), danhSach.end(), targetId, [](const SinhVien& sv, const string& id) {
        return sv.msv < id;
    });
    auto end = high_resolution_clock::now();

    if (it != danhSach.end() && it->msv == targetId) {
        cout << "Sinh vien tim thay: " << *it << endl;
    } else {
        cout << "Khong tim thay sinh vien voi ma: " << targetId << endl;
    }

    size_t memoryUsage = sizeof(SinhVien) * danhSach.size() + sizeof(danhSach);
    cout << "Thoi gian tim kiem: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";
    cout << "Dung luong bo nho su dung: " << memoryUsage / 1024.0 << " KB\n";
}

// === Bubble Sort ===
void bubbleSort(vector<SinhVien>& arr, const function<bool(const SinhVien&, const SinhVien&)>& compare) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compare(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortMain() {
    vector<SinhVien> danhSach = docFileCSV("data.csv");
    if (danhSach.empty()) {
        cerr << "Khong co du lieu hop le trong file.\n";
        return;
    }

    auto start = high_resolution_clock::now();
    bubbleSort(danhSach, [](const SinhVien& a, const SinhVien& b) {
        return a.diemTBM < b.diemTBM;
    });
    auto end = high_resolution_clock::now();

    ghiFileCSV(danhSach, "ket_qua_bubble_sort.csv");
    size_t memoryUsage = sizeof(SinhVien) * danhSach.size() + sizeof(danhSach);
    cout << "Da sap xep bang Bubble Sort va ghi ket qua vao file.\n";
    cout << "Thoi gian sap xep: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";
    cout << "Dung luong bo nho su dung: " << memoryUsage / 1024.0 << " KB\n";
}

// === Quick Sort ===
void quickSort(vector<SinhVien>& arr, int low, int high, const function<bool(const SinhVien&, const SinhVien&)>& compare) {
    if (low < high) {
        int pivot = low;
        for (int i = low + 1; i <= high; ++i) {
            if (compare(arr[i], arr[low])) {
                swap(arr[++pivot], arr[i]);
            }
        }
        swap(arr[low], arr[pivot]);
        quickSort(arr, low, pivot - 1, compare);
        quickSort(arr, pivot + 1, high, compare);
    }
}

void quickSortMain() {
    vector<SinhVien> danhSach = docFileCSV("data.csv");
    if (danhSach.empty()) {
        cerr << "Khong co du lieu hop le trong file.\n";
        return;
    }

    auto start = high_resolution_clock::now();
    quickSort(danhSach, 0, danhSach.size() - 1, [](const SinhVien& a, const SinhVien& b) {
        return a.diemTBM < b.diemTBM;
    });
    auto end = high_resolution_clock::now();

    ghiFileCSV(danhSach, "ket_qua_quick_sort.csv");
    size_t memoryUsage = sizeof(SinhVien) * danhSach.size() + sizeof(danhSach);
    cout << "Da sap xep bang Quick Sort va ghi ket qua vao file.\n";
    cout << "Thoi gian sap xep: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";
    cout << "Dung luong bo nho su dung: " << memoryUsage / 1024.0 << " KB\n";
}

// === Merge Sort ===
void merge(vector<SinhVien>& arr, int left, int mid, int right, const function<bool(const SinhVien&, const SinhVien&)>& compare) {
    vector<SinhVien> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<SinhVien> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (compare(leftArr[i], rightArr[j])) {
            arr[k++] = move(leftArr[i++]);
        } else {
            arr[k++] = move(rightArr[j++]);
        }
    }

    while (i < leftArr.size()) arr[k++] = move(leftArr[i++]);
    while (j < rightArr.size()) arr[k++] = move(rightArr[j++]);
}

void mergeSort(vector<SinhVien>& arr, int left, int right, const function<bool(const SinhVien&, const SinhVien&)>& compare) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, compare);
        mergeSort(arr, mid + 1, right, compare);
        merge(arr, left, mid, right, compare);
    }
}

void mergeSortMain() {
    vector<SinhVien> danhSach = docFileCSV("data.csv");
    if (danhSach.empty()) {
        cerr << "Khong co du lieu hop le trong file.\n";
        return;
    }

    auto start = high_resolution_clock::now();
    mergeSort(danhSach, 0, danhSach.size() - 1, [](const SinhVien& a, const SinhVien& b) {
        return a.diemTBM < b.diemTBM;
    });
    auto end = high_resolution_clock::now();

    ghiFileCSV(danhSach, "ket_qua_merge_sort.csv");
    size_t memoryUsage = sizeof(SinhVien) * danhSach.size() + sizeof(danhSach);
    cout << "Da sap xep bang Merge Sort va ghi ket qua vao file.\n";
    cout << "Thoi gian sap xep: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";
    cout << "Dung luong bo nho su dung: " << memoryUsage / 1024.0 << " KB\n";
}

// === Menu chính ===
void menu() {
    int choice;
    do {
        cout << "=== Menu Chinh ===\n";
        cout << "1. Thao tac tim kiem\n";
        cout << "2. Thao tac sap xep\n";
        cout << "3. Thoat\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int searchChoice;
                cout << "1. Linear Search\n2. Binary Search\n3. Quay lai\nLua chon: ";
                cin >> searchChoice;
                if (searchChoice == 1) linearSearchMain();
                else if (searchChoice == 2) binarySearchMain();
                break;
            }
            case 2: {
                int sortChoice;
                cout << "1. Bubble Sort\n2. Quick Sort\n3. Merge Sort\n4. Quay lai\nLua chon: ";
                cin >> sortChoice;
                if (sortChoice == 1) bubbleSortMain();
                else if (sortChoice == 2) quickSortMain();
                else if (sortChoice == 3) mergeSortMain();
                break;
            }
            case 3:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 3);
}

int main() {
    menu();
    return 0;
}