#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // Để đọc/ghi file
#include <sstream>      // Để xử lý chuỗi (tách dòng CSV)
#include <algorithm>    // Cho swap, all_of
#include <chrono>       // Để đo thời gian
#include <functional>   // Cho function (để truyền hàm so sánh)
#include <random>       // Cho pivot ngẫu nhiên
#include <limits>       // Cho numeric_limits
#include <iomanip>      // Cho setprecision, fixed
#include <cctype>       // Cho ::isspace (kiểm tra khoảng trắng)
#include <stdexcept>    // Cho các exception chuẩn (stod)

using namespace std;
using namespace chrono; 
// --- Bước 1: Định nghĩa cấu trúc SinhVien ---
struct SinhVien {
    string msv;
    string hoTen;
    double diemTBM;

    // Hàm tạo
    SinhVien(string m = "", string t = "", double d = 0.0)
        : msv(move(m)), hoTen(move(t)), diemTBM(d) {} // Sử dụng move

    // Toán tử << để ghi ra file CSV
    friend ostream& operator<<(ostream& os, const SinhVien& sv) {
        os << sv.msv << "," << sv.hoTen << "," << fixed << setprecision(2) << sv.diemTBM;
        return os;
    }
};

// --- Bước 2: Hàm đọc file CSV ---
// Đọc dữ liệu từ cấu trúc: STT,Ho va ten,Ma sinh vien,...,TBM
vector<SinhVien> docFileCSV(const string& tenFile) {
    vector<SinhVien> dsSinhVien;
    ifstream file(tenFile);
    string line;

    if (!file.is_open()) {
        cerr << "Loi: Khong the mo file " << tenFile << endl;
        return dsSinhVien; // Trả về vector rỗng
    }

    // Bỏ qua dòng header
    if (getline(file, line)) {
        // cout << "Doc header: " << line << endl; // Bỏ comment nếu muốn xem header
    } else {
        cerr << "Loi: File rong hoac khong doc duoc header." << endl;
        return dsSinhVien;
    }

    int lineNumber = 1; // Bắt đầu từ dòng dữ liệu đầu tiên (sau header)
    // Đọc từng dòng dữ liệu
    while (getline(file, line)) {
        lineNumber++;
        // Bỏ qua các dòng trống
        if (line.empty() || all_of(line.begin(), line.end(), ::isspace)) {
            continue;
        }

        stringstream ss(line);
        string segment;
        vector<string> data;

        // Tách các cột bằng dấu phẩy
        while (getline(ss, segment, ',')) {
            // Loại bỏ khoảng trắng thừa ở đầu và cuối mỗi segment
            segment.erase(0, segment.find_first_not_of(" \t\n\r\f\v"));
            segment.erase(segment.find_last_not_of(" \t\n\r\f\v") + 1);
            data.push_back(segment);
        }

        // Kiểm tra xem có đủ 8 cột không
        if (data.size() >= 8) {
            try {
                // Lấy dữ liệu từ các cột cần thiết
                string hoTen = data[1]; // Cột thứ 2 (index 1)
                string msv = data[2];   // Cột thứ 3 (index 2)
                double diemTBM = stod(data[7]); // Cột thứ 8 (index 7), dùng stod từ <string>

                // Thêm sinh viên vào danh sách
                dsSinhVien.emplace_back(msv, hoTen, diemTBM);

            } catch (const invalid_argument& e) {
                cerr << "Loi dinh dang so TBM o dong " << lineNumber << ": '" << (data.size() > 7 ? data[7] : "N/A") << "' - " << e.what() << endl;
            } catch (const out_of_range& e) {
                 cerr << "Loi tran so TBM o dong " << lineNumber << ": '" << (data.size() > 7 ? data[7] : "N/A") << "' - " << e.what() << endl;
            } catch (const exception& e) { // Bắt các lỗi khác
                 cerr << "Loi khac o dong " << lineNumber << ": " << e.what() << endl;
            }
        } else {
             cerr << "Canh bao: Dong " << lineNumber << " khong du 8 cot (" << data.size() << " cot): Bo qua dong nay." << endl;
        }
    }

    file.close();
    return dsSinhVien;
}


// --- Bước 3: Triển khai QuickSort ---

// Enum để chọn loại Pivot
enum class PivotType {
    FIRST, LAST, MIDDLE, RANDOM
};

// Hàm so sánh cho QuickSort
using Comparator = function<bool(const SinhVien&, const SinhVien&)>;

// --- Hàm Partition (Lomuto partition scheme) ---
int partition(vector<SinhVien>& arr, int low, int high, PivotType pivotType, const Comparator& compare) {
    int pivotIndex;

    // 1. Chọn Pivot Index
    switch (pivotType) {
        case PivotType::MIDDLE: {
            pivotIndex = low + (high - low) / 2;
            break;
        }
        case PivotType::RANDOM: {
            // Khởi tạo bộ sinh số ngẫu nhiên một lần để hiệu quả hơn nếu gọi nhiều lần
            static mt19937 gen(random_device{}()); // random_device, mt19937 từ <random>
            uniform_int_distribution<> distrib(low, high); // uniform_int_distribution từ <random>
            pivotIndex = distrib(gen);
            break;
        }
        case PivotType::LAST: {
            pivotIndex = high;
            break;
        }
        case PivotType::FIRST:
        default: {
            pivotIndex = low;
            break;
        }
    }

    // Đưa pivot được chọn về cuối để tiện xử lý (theo Lomuto)
    swap(arr[pivotIndex], arr[high]); // swap từ <algorithm>
    const SinhVien& pivotValue = arr[high];

    // 2. Phân hoạch
    int i = low - 1; // Chỉ số của phần tử cuối cùng <= pivot

    for (int j = low; j < high; ++j) {
        // Nếu phần tử hiện tại < pivot theo tiêu chí so sánh
        if (compare(arr[j], pivotValue)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // Đưa pivot về đúng vị trí
    swap(arr[i + 1], arr[high]);
    return (i + 1); // Trả về chỉ số cuối cùng của pivot
}

// --- Hàm QuickSort chính (đệ quy) ---
void quickSort(vector<SinhVien>& arr, int low, int high, PivotType pivotType, const Comparator& compare) {
    if (low < high && low >= 0 && high < arr.size()) { // Thêm kiểm tra biên low/high
        int pi = partition(arr, low, high, pivotType, compare);
        quickSort(arr, low, pi - 1, pivotType, compare);
        quickSort(arr, pi + 1, high, pivotType, compare);
    }
}

// --- Các hàm so sánh cụ thể ---
bool soSanhTheoTBM(const SinhVien& a, const SinhVien& b) {
    return a.diemTBM < b.diemTBM; // Từ bé đến lớn
}

bool soSanhTheoTBMGiam(const SinhVien& a, const SinhVien& b) {
    return a.diemTBM > b.diemTBM; // Từ cao đến thấp
}

bool soSanhTheoMSV(const SinhVien& a, const SinhVien& b) {
    return a.msv < b.msv; // So sánh chuỗi theo thứ tự từ điển
}

bool soSanhTheoTen(const SinhVien& a, const SinhVien& b) {
    // Lưu ý: Để sắp xếp chính xác theo TÊN, cần tách tên ra khỏi họ đệm.
    return a.hoTen < b.hoTen; // So sánh cả chuỗi họ tên
}


// --- Bước 4: Hàm ghi file CSV ---
bool ghiFileCSV(const string& tenFile, const vector<SinhVien>& dsSinhVien) {
    ofstream file(tenFile);

    if (!file.is_open()) {
        cerr << "Loi: Khong the mo file de ghi " << tenFile << endl;
        return false;
    }

    // Ghi header
    file << "MSV,HoTen,DiemTBM\n";

    // Ghi dữ liệu từng sinh viên
    for (const auto& sv : dsSinhVien) {
        file << sv << "\n"; // Sử dụng toán tử << đã nạp chồng
    }

    file.close();
    return file.good(); // Kiểm tra lỗi I/O khi đóng file
}

// --- Bước 5: Hàm đo dung lượng bộ nhớ (Ước lượng) ---
size_t uocLuongBoNho(const vector<SinhVien>& ds) {
    size_t size = sizeof(vector<SinhVien>);
    size += ds.capacity() * sizeof(SinhVien);
    for(const auto& sv : ds) {
        size += sv.msv.capacity() * sizeof(char);
        size += sv.hoTen.capacity() * sizeof(char);
    }
    return size;
}


// --- Bước 6: Giao diện người dùng và Hàm main (Đo bằng nanosecond) ---
int main() {
    string fileInput = "data.csv"; // Tên file mặc định
    string fileOutput = "ket_qua_sap_xep_quicksort.csv";

    int luaChonSapXep;
    int luaChonPivot;

    // --- Hỏi tên file Input ---
    cout << "Nhap ten file CSV dau vao (nhan Enter de dung mac dinh 'data.csv'): ";
    string tempInput;
    getline(cin, tempInput);
    if (!tempInput.empty()) {
        fileInput = tempInput;
    }

    // --- Đọc dữ liệu ---
    cout << "Dang doc file '" << fileInput << "'..." << endl;
    auto startRead = high_resolution_clock::now(); // high_resolution_clock từ <chrono>
    vector<SinhVien> danhSachSV = docFileCSV(fileInput);
    auto endRead = high_resolution_clock::now();
    duration<double, milli> readDuration = endRead - startRead; // duration, milli từ <chrono>

    if (danhSachSV.empty()) {
        cerr << "Khong co du lieu hop le de sap xep tu file '" << fileInput << "'. Ket thuc." << endl;
        return 1;
    }
    cout << "Doc thanh cong " << danhSachSV.size() << " sinh vien trong "
              << fixed << setprecision(4) << readDuration.count() << " ms." << endl; // fixed, setprecision từ <iomanip>
    cout << "------------------------------------------" << endl;

    // --- Lấy lựa chọn sắp xếp ---
    cout << "Chon tieu chi sap xep:" << endl;
    cout << "1. Diem TBM (thap -> cao)" << endl;
    cout << "2. Diem TBM (cao -> thap)" << endl;
    cout << "3. Ma Sinh Vien (A -> Z)" << endl;
    cout << "4. Ten (A -> Z theo Ho va Ten)" << endl;
    cout << "Lua chon cua ban (1-4): ";
    while (!(cin >> luaChonSapXep) || luaChonSapXep < 1 || luaChonSapXep > 4) { // Cập nhật phạm vi kiểm tra
        cout << "Lua chon khong hop le. Vui long nhap lai (1-4): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // numeric_limits, streamsize từ <limits>
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Lấy lựa chọn Pivot ---
    cout << "\nChon cach chon Pivot cho QuickSort:" << endl;
    cout << "1. Pivot o dau" << endl;
    cout << "2. Pivot o cuoi" << endl;
    cout << "3. Pivot o giua" << endl;
    cout << "4. Pivot ngau nhien" << endl;
    cout << "Lua chon cua ban (1-4): ";
    while (!(cin >> luaChonPivot) || luaChonPivot < 1 || luaChonPivot > 4) {
        cout << "Lua chon khong hop le. Vui long nhap lai (1-4): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Hỏi tên file Output ---
    cout << "\nNhap ten file CSV dau ra (nhan Enter de dung mac dinh '" << fileOutput << "'): ";
    string tempOutput;
    getline(cin, tempOutput);
    if (!tempOutput.empty()) {
        fileOutput = tempOutput;
    }

    // --- Chọn hàm so sánh và loại pivot ---
    Comparator hamSoSanh; // Comparator đã using ở trên
    string tieuChiStr;
    switch (luaChonSapXep) {
        case 1: hamSoSanh = soSanhTheoTBM; tieuChiStr = "Diem TBM (thap -> cao)"; break;
        case 2: hamSoSanh = soSanhTheoTBMGiam; tieuChiStr = "Diem TBM (cao -> thap)"; break;
        case 3: hamSoSanh = soSanhTheoMSV; tieuChiStr = "Ma Sinh Vien"; break;
        case 4: hamSoSanh = soSanhTheoTen; tieuChiStr = "Ten"; break;
        default: hamSoSanh = soSanhTheoMSV; tieuChiStr = "Ma Sinh Vien (default)";
    }

    PivotType loaiPivot; // PivotType đã định nghĩa
    string pivotStr;
    switch (luaChonPivot) {
        case 1: loaiPivot = PivotType::FIRST; pivotStr = "Dau"; break;
        case 2: loaiPivot = PivotType::LAST; pivotStr = "Cuoi"; break;
        case 3: loaiPivot = PivotType::MIDDLE; pivotStr = "Giua"; break;
        case 4: loaiPivot = PivotType::RANDOM; pivotStr = "Ngau nhien"; break;
        default: loaiPivot = PivotType::LAST; pivotStr = "Cuoi (default)";
    }

    // --- Thực hiện sắp xếp nhiều lần và đo thời gian bằng nanosecond ---
    const int soLanLap = 100;
    nanoseconds tongThoiGianSort(0); // nanoseconds từ <chrono>

    cout << "\nDang thuc hien QuickSort " << soLanLap << " lan theo '" << tieuChiStr
              << "' voi Pivot '" << pivotStr << "' de tinh trung binh..." << endl;

    vector<SinhVien> danhSachGoc = danhSachSV;

    for (int i = 0; i < soLanLap; ++i) {
        vector<SinhVien> danhSachSao = danhSachGoc;

        auto startTime = high_resolution_clock::now();
        if (!danhSachSao.empty()) {
            quickSort(danhSachSao, 0, static_cast<int>(danhSachSao.size() - 1), loaiPivot, hamSoSanh);
        }
        auto endTime = high_resolution_clock::now();
        tongThoiGianSort += duration_cast<nanoseconds>(endTime - startTime); // duration_cast từ <chrono>
    }

    // Sắp xếp lại danh sách gốc một lần cuối để ghi ra file
    cout << "Sap xep lan cuoi de ghi file..." << endl;
     if (!danhSachSV.empty()) {
          quickSort(danhSachSV, 0, static_cast<int>(danhSachSV.size() - 1), loaiPivot, hamSoSanh);
     }
    cout << "Sap xep hoan tat." << endl;

    // Tính thời gian trung bình
    double thoiGianTrungBinhNs = (tongThoiGianSort.count()) / static_cast<double>(soLanLap);


    // --- Hiển thị kết quả hiệu năng ---
    cout << "------------------------------------------" << endl;
    cout << "KET QUA THUC THI (QuickSort):" << endl;
    cout << "- Thoi gian doc file:         "
              << fixed << setprecision(4) << readDuration.count() << " ms" << endl;
    cout << "- Thoi gian trung binh QuickSort: "
              << fixed << setprecision(2) << thoiGianTrungBinhNs << " ns" << endl; // Hiển thị trung bình nanosecond

    // Ước lượng bộ nhớ
    size_t memoryUsageBytes = uocLuongBoNho(danhSachSV);
    double memoryUsageMB = static_cast<double>(memoryUsageBytes) / (1024.0 * 1024.0);
    cout << "- Uoc luong dung luong bo nho (vector data): ~"
              << fixed << setprecision(4) << memoryUsageMB << " MB" << endl;
    cout << "  (Luu y: Day chi la uoc tinh bo nho cho vector chua du lieu.)" << endl;
    cout << "------------------------------------------" << endl;

    // --- Ghi kết quả ra file ---
    cout << "Dang ghi ket qua da sap xep ra file '" << fileOutput << "'..." << endl;
    if (ghiFileCSV(fileOutput, danhSachSV)) {
        cout << "Ghi file thanh cong!" << endl;
    } else {
        cerr << "Ghi file that bai." << endl;
    }

    return 0;
}