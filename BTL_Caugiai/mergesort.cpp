#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct SinhVien {
    string msv;
    string hoTen;
    double diemTBM;

    friend ostream& operator<<(ostream& os, const SinhVien& sv) {
        os << sv.msv << "," << sv.hoTen << "," << fixed << setprecision(2) << sv.diemTBM;
        return os;
    }
};

// Hàm đọc file CSV
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

// Merge Sort
void merge(vector<SinhVien>& arr, int left, int mid, int right, const function<bool(const SinhVien&, const SinhVien&)>& comp) {
    vector<SinhVien> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<SinhVien> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
        if (comp(leftArr[i], rightArr[j])) {
            arr[k++] = move(leftArr[i++]);
        } else {
            arr[k++] = move(rightArr[j++]);
        }
    }

    while (i < (int)leftArr.size()) arr[k++] = move(leftArr[i++]);
    while (j < (int)rightArr.size()) arr[k++] = move(rightArr[j++]);
}

void mergeSort(vector<SinhVien>& arr, int left, int right, const function<bool(const SinhVien&, const SinhVien&)>& comp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comp);
    mergeSort(arr, mid + 1, right, comp);
    merge(arr, left, mid, right, comp);
}

// Ghi danh sách ra file CSV
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

// Ước lượng bộ nhớ
size_t uocLuongBoNho(const vector<SinhVien>& danhSach) {
    size_t total = sizeof(SinhVien) * danhSach.size();
    for (const auto& sv : danhSach) {
        total += sv.msv.capacity() + sv.hoTen.capacity();
    }
    return total;
}

int main() {
    string tenFile;
    cout << "Nhap ten file CSV (nhan Enter de dung mac dinh: data.csv): ";
    getline(cin, tenFile);
    if (tenFile.empty()) {
        tenFile = "data.csv";
    }

    auto startDoc = high_resolution_clock::now();
    auto danhSach = docFileCSV(tenFile);
    auto stopDoc = high_resolution_clock::now();
    auto durationDoc = duration_cast<microseconds>(stopDoc - startDoc);
    cout << "Doc file mat: " << durationDoc.count() << " microseconds\n";

    if (danhSach.empty()) {
        cerr << "Khong co du lieu hop le trong file.\n";
        cout << "Nhan Enter de thoat...";
        cin.get();
        return 1;
    }

    cout << "Chon tieu chi sap xep:\n";
    cout << "1. Theo diem TBM\n2. Theo ma sinh vien\n3. Theo ho va ten\n";
    int tieuChi;
    cin >> tieuChi;

    function<bool(const SinhVien&, const SinhVien&)> soSanh;

    switch (tieuChi) {
        case 1:
            soSanh = [](const SinhVien& a, const SinhVien& b) {
                return a.diemTBM < b.diemTBM;
            };
            break;
        case 2:
            soSanh = [](const SinhVien& a, const SinhVien& b) {
                return a.msv < b.msv;
            };
            break;
        case 3:
            soSanh = [](const SinhVien& a, const SinhVien& b) {
                return a.hoTen < b.hoTen;
            };
            break;
        default:
            cerr << "Tieu chi khong hop le.\n";
            cout << "Nhan Enter de thoat...";
            cin.ignore();
            cin.get();
            return 1;
    }

    const int soLanLap = 100;
auto tongThoiGian = nanoseconds(0);

for (int i = 0; i < soLanLap; ++i) {
    auto danhSachSao = danhSach; // copy danh sách ban đầu

    auto batDau = high_resolution_clock::now();
    mergeSort(danhSachSao, 0, danhSachSao.size() - 1, soSanh);
    auto ketThuc = high_resolution_clock::now();

    tongThoiGian += duration_cast<nanoseconds>(ketThuc - batDau);
}

// Sắp xếp lại lần cuối để ghi ra file
mergeSort(danhSach, 0, danhSach.size() - 1, soSanh);

double thoiGianTrungBinhNs = tongThoiGian.count() / static_cast<double>(soLanLap);

    cin.ignore(); // Dọn bộ đệm trước khi nhập tiếp

    string tenFileKetQua;
    cout << "Nhap ten file ket qua (nhan Enter de dung mac dinh: ket_qua_sap_xep.csv): ";
    getline(cin, tenFileKetQua);
    if (tenFileKetQua.empty()) {
        tenFileKetQua = "ket_qua_sap_xep.csv";
    }

    ghiFileCSV(danhSach, tenFileKetQua);

    cout << "\n=== Thong tin thuc thi ===\n";
    cout << "Da sap xep va ghi ket qua vao file: " << tenFileKetQua << endl;
    cout << "Thoi gian sap xep 100 lan: " << tongThoiGian.count() << " ns\n";
    cout << "Thoi gian sap xep trung binh: " << thoiGianTrungBinhNs << " ns\n";
    cout << "Uoc luong bo nho da su dung: " << uocLuongBoNho(danhSach) / 1024.0 << " KB\n";

    cout << "Nhan Enter de thoat...";
    cin.get();
    return 0;
}
