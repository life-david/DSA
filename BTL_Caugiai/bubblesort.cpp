#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // Để đọc/ghi file
#include <sstream>      // Để xử lý chuỗi (tách dòng CSV)
#include <algorithm>    // Cho std::swap, std::all_of
#include <chrono>       // Để đo thời gian
#include <functional>   // Cho std::function (để truyền hàm so sánh)
#include <limits>       // Cho numeric_limits
#include <iomanip>      // Cho setprecision, fixed
#include <cctype>       // Cho ::isspace (kiểm tra khoảng trắng)
#include <stdexcept>    // Cho các exception chuẩn (stod)


struct SinhVien {
    std::string msv;
    std::string hoTen;
    double diemTBM;

    // Hàm tạo
    SinhVien(std::string m = "", std::string t = "", double d = 0.0)
        : msv(std::move(m)), hoTen(std::move(t)), diemTBM(d) {} // Sử dụng std::move

    // Toán tử << để ghi ra file CSV (nhất quán với ví dụ trước)
    friend std::ostream& operator<<(std::ostream& os, const SinhVien& sv) {
        os << sv.msv << "," << sv.hoTen << "," << std::fixed << std::setprecision(2) << sv.diemTBM;
        return os;
    }
};

// --- Bước 2: Hàm đọc file CSV (Cải tiến từ cả hai ví dụ) ---
// Đọc dữ liệu từ cấu trúc: STT,Ho va ten,Ma sinh vien,...,TBM
std::vector<SinhVien> docFileCSV(const std::string& tenFile) {
    std::vector<SinhVien> dsSinhVien;
    std::ifstream file(tenFile);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Loi: Khong the mo file " << tenFile << std::endl;
        return dsSinhVien; // Trả về vector rỗng
    }

    // Bỏ qua dòng header
    if (std::getline(file, line)) {
        // std::cout << "Doc header: " << line << std::endl; // Có thể bỏ comment nếu muốn xem header
    } else {
        std::cerr << "Loi: File rong hoac khong doc duoc header." << std::endl;
        return dsSinhVien;
    }

    int lineNumber = 1; // Bắt đầu từ dòng dữ liệu đầu tiên (sau header)
    // Đọc từng dòng dữ liệu
    while (std::getline(file, line)) {
        lineNumber++;
        // Bỏ qua các dòng trống
        if (line.empty() || std::all_of(line.begin(), line.end(), ::isspace)) {
            continue;
        }

        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> data;

        // Tách các cột bằng dấu phẩy
        while (std::getline(ss, segment, ',')) {
            // Loại bỏ khoảng trắng thừa ở đầu và cuối mỗi segment
            segment.erase(0, segment.find_first_not_of(" \t\n\r\f\v"));
            segment.erase(segment.find_last_not_of(" \t\n\r\f\v") + 1);
            data.push_back(segment);
        }

        // Kiểm tra xem có đủ 8 cột không (dựa trên cấu trúc file giả định)
        if (data.size() >= 8) {
            try {
                // Lấy dữ liệu từ các cột cần thiết
                std::string hoTen = data[1]; // Cột thứ 2 (index 1)
                std::string msv = data[2];   // Cột thứ 3 (index 2)
                double diemTBM = std::stod(data[7]); // Cột thứ 8 (index 7)

                // Thêm sinh viên vào danh sách
                dsSinhVien.emplace_back(msv, hoTen, diemTBM);

            } catch (const std::invalid_argument& e) {
                std::cerr << "Loi dinh dang so TBM o dong " << lineNumber << ": '" << (data.size() > 7 ? data[7] : "N/A") << "' - " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                 std::cerr << "Loi tran so TBM o dong " << lineNumber << ": '" << (data.size() > 7 ? data[7] : "N/A") << "' - " << e.what() << std::endl;
            } catch (const std::exception& e) { // Bắt các lỗi khác
                 std::cerr << "Loi khac o dong " << lineNumber << ": " << e.what() << std::endl;
            }
        } else {
             std::cerr << "Canh bao: Dong " << lineNumber << " khong du 8 cot (" << data.size() << " cot): Bo qua dong nay." << std::endl;
        }
    }

    file.close();
    return dsSinhVien;
}

// --- Bước 3: Triển khai BubbleSort (Sử dụng Comparator) ---

// Hàm so sánh cho các thuật toán sắp xếp
using Comparator = std::function<bool(const SinhVien&, const SinhVien&)>;

// Bubble Sort (cải tiến để dùng Comparator)
// Tham số `verbose` để bật/tắt in chi tiết các bước (mặc định là tắt)
void bubbleSort(std::vector<SinhVien>& arr, const Comparator& compare, bool verbose = false) {
    int n = arr.size();
    bool swapped; // Biến để kiểm tra xem có swap trong lần lặp không (cải tiến Bubble Sort)
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        if (verbose) {
             std::cout << "Vong lap thu " << i + 1 << ":" << std::endl;
        }
        for (int j = 0; j < n - i - 1; ++j) {
            // Sử dụng hàm so sánh được truyền vào
            // compare(a, b) trả về true nếu a < b theo tiêu chí sắp xếp
            // Do đó, nếu compare(arr[j+1], arr[j]) là true, nghĩa là arr[j+1] < arr[j]
            // -> cần đổi chỗ để đưa phần tử lớn hơn về cuối (sắp xếp tăng dần)
            if (compare(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
                if (verbose) {
                    std::cout << "  Hoan doi: (" << arr[j].msv << ", " << arr[j].diemTBM
                              << ") <-> (" << arr[j+1].msv << ", " << arr[j+1].diemTBM << ")" << std::endl;
                }
            }
        }

        // Nếu không có swap nào trong lần lặp -> mảng đã được sắp xếp
        if (!swapped) {
            if (verbose) std::cout << "Mang da sap xep tai vong lap " << i+1 << ". Ket thuc som." << std::endl;
            break;
        }

        if (verbose) {
            std::cout << "  Trang thai danh sach sau vong lap " << i + 1 << ":" << std::endl;
            for (size_t k = 0; k < arr.size(); ++k) { // Dùng size_t cho index vector
                 std::cout << "    " << arr[k].msv << ", " << arr[k].hoTen << ", " << std::fixed << std::setprecision(2) << arr[k].diemTBM << std::endl;
            }
             std::cout << "------------------------------------------" << std::endl;
        }
    }
}

// --- Các hàm so sánh cụ thể (giống ví dụ trước) ---
bool soSanhTheoTBM(const SinhVien& a, const SinhVien& b) {
    return a.diemTBM < b.diemTBM; // Từ bé đến lớn
    // Nếu muốn sắp xếp TBM bằng nhau theo MSV thì thêm logic:
    // if (a.diemTBM != b.diemTBM) {
    //     return a.diemTBM < b.diemTBM;
    // }
    // return a.msv < b.msv; // Nếu TBM bằng nhau, sắp xếp theo MSV
}

bool soSanhTheoMSV(const SinhVien& a, const SinhVien& b) {
    return a.msv < b.msv; // So sánh chuỗi theo thứ tự từ điển
}

bool soSanhTheoTen(const SinhVien& a, const SinhVien& b) {
    // So sánh chuỗi HoTen theo thứ tự từ điển
    // Lưu ý: Để sắp xếp chính xác theo TÊN, cần tách tên ra khỏi họ đệm.
    return a.hoTen < b.hoTen;
}

// --- Bước 4: Hàm ghi file CSV (giống ví dụ trước) ---
bool ghiFileCSV(const std::string& tenFile, const std::vector<SinhVien>& dsSinhVien) {
    std::ofstream file(tenFile);

    if (!file.is_open()) {
        std::cerr << "Loi: Khong the mo file de ghi " << tenFile << std::endl;
        return false;
    }

    // Ghi header (chỉ gồm các cột có trong struct SinhVien)
    file << "MSV,HoTen,DiemTBM\n";

    // Ghi dữ liệu từng sinh viên
    for (const auto& sv : dsSinhVien) {
        file << sv << "\n"; // Sử dụng toán tử << đã nạp chồng
    }

    file.close();
    // Kiểm tra xem việc đóng file có thành công không
    return file.good();
}

// --- Bước 5: Hàm đo dung lượng bộ nhớ (Ước lượng giống ví dụ trước) ---
size_t uocLuongBoNhoVector(const std::vector<SinhVien>& ds) {
    size_t size = sizeof(std::vector<SinhVien>); // Kích thước cấu trúc vector
    size += ds.capacity() * sizeof(SinhVien);     // Bộ nhớ cấp phát cho con trỏ/dữ liệu cơ bản
    // Cộng thêm bộ nhớ cấp phát động cho các chuỗi string
    for(const auto& sv : ds) {
        size += sv.msv.capacity() * sizeof(char); // Bộ nhớ thực cấp cho chuỗi msv
        size += sv.hoTen.capacity() * sizeof(char);// Bộ nhớ thực cấp cho chuỗi hoTen
    }
    return size;
}

// --- Bước 6: Giao diện người dùng và Hàm main (tương tự ví dụ trước) ---
int main() {
    std::string fileInput = "data.csv"; // Tên file mặc định
    std::string fileOutput = "ket_qua_bubble_sort.csv"; // Đổi tên file output mặc định

    int luaChonSapXep;
    // bool chiTietSapXep = false; // Biến để bật/tắt in chi tiết các bước BubbleSort

    // --- Hỏi tên file Input ---
    std::cout << "Nhap ten file CSV dau vao (nhan Enter de dung mac dinh 'data.csv'): ";
    std::string tempInput;
    std::getline(std::cin, tempInput);
    if (!tempInput.empty()) {
        fileInput = tempInput;
    }

    // --- Đọc dữ liệu ---
    std::cout << "Dang doc file '" << fileInput << "'..." << std::endl;
    auto startRead = std::chrono::high_resolution_clock::now();
    std::vector<SinhVien> danhSachSV = docFileCSV(fileInput);
    auto endRead = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> readDuration = endRead - startRead;

    if (danhSachSV.empty()) {
        std::cerr << "Khong co du lieu hop le de sap xep tu file '" << fileInput << "'. Ket thuc." << std::endl;
        return 1;
    }
    std::cout << "Doc thanh cong " << danhSachSV.size() << " sinh vien trong " << readDuration.count() << " ms." << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // --- Lấy lựa chọn sắp xếp ---
    std::cout << "Chon tieu chi sap xep (Bubble Sort):" << std::endl;
    std::cout << "1. Diem TBM (thap -> cao)" << std::endl;
    std::cout << "2. Ma Sinh Vien (A -> Z)" << std::endl;
    std::cout << "3. Ten (A -> Z theo Ho va Ten)" << std::endl;
    std::cout << "Lua chon cua ban (1-3): ";
    while (!(std::cin >> luaChonSapXep) || luaChonSapXep < 1 || luaChonSapXep > 3) {
        std::cout << "Lua chon khong hop le. Vui long nhap lai (1-3): ";
        std::cin.clear(); // Xóa trạng thái lỗi của cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua phần input lỗi
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua ký tự Enter còn sót lại

     // --- Hỏi có muốn xem chi tiết các bước sắp xếp không ---
     // char xemChiTiet;
     // std::cout << "\nBan co muon xem chi tiet cac buoc hoan doi cua Bubble Sort khong? (Y/N): ";
     // std::cin >> xemChiTiet;
     // chiTietSapXep = (std::toupper(xemChiTiet) == 'Y');
     // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // --- Hỏi tên file Output ---
    std::cout << "\nNhap ten file CSV dau ra (nhan Enter de dung mac dinh '" << fileOutput << "'): ";
    std::string tempOutput;
    std::getline(std::cin, tempOutput);
    if (!tempOutput.empty()) {
        fileOutput = tempOutput;
    }

    // --- Chọn hàm so sánh ---
    Comparator hamSoSanh;
    std::string tieuChiStr;
    switch (luaChonSapXep) {
        case 1: hamSoSanh = soSanhTheoTBM; tieuChiStr = "Diem TBM"; break;
        case 2: hamSoSanh = soSanhTheoMSV; tieuChiStr = "Ma Sinh Vien"; break;
        case 3: hamSoSanh = soSanhTheoTen; tieuChiStr = "Ten"; break;
        default: hamSoSanh = soSanhTheoMSV; tieuChiStr = "Ma Sinh Vien (default)"; // Fallback
    }

    // --- Thực hiện sắp xếp và đo thời gian ---
    std::cout << "\nDang thuc hien Bubble Sort theo '" << tieuChiStr << "'..." << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now(); // Bắt đầu đo Bubble Sort

    // Gọi BubbleSort với vector dữ liệu và hàm so sánh đã chọn
    if (!danhSachSV.empty()) {
         // bubbleSort(danhSachSV, hamSoSanh, chiTietSapXep); // Gọi với tùy chọn xem chi tiết
         bubbleSort(danhSachSV, hamSoSanh); // Gọi bản không xem chi tiết
    }

    auto endTime = std::chrono::high_resolution_clock::now(); // Kết thúc đo Bubble Sort
    std::chrono::duration<double, std::milli> sortDuration = endTime - startTime; // Tính thời gian (ms)
    std::cout << "Sap xep hoan tat." << std::endl;

    // --- Hiển thị kết quả hiệu năng ---
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "KET QUA THUC THI (Bubble Sort):" << std::endl;
     std::cout << "- Thoi gian doc file:       "
               << std::fixed << std::setprecision(4) << readDuration.count() << " ms" << std::endl;
    std::cout << "- Thoi gian chay Bubble Sort: "
              << std::fixed << std::setprecision(4) << sortDuration.count() << " ms" << std::endl;

    // Ước lượng bộ nhớ (cách giống ví dụ QuickSort)
    size_t memoryUsageBytes = uocLuongBoNhoVector(danhSachSV);
    double memoryUsageMB = static_cast<double>(memoryUsageBytes) / (1024.0 * 1024.0);
    std::cout << "- Uoc luong dung luong bo nho (vector data): ~"
              << std::fixed << std::setprecision(4) << memoryUsageMB << " MB" << std::endl;
    std::cout << "  (Luu y: Day chi la uoc tinh bo nho cho vector chua du lieu.)" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // --- Ghi kết quả ra file ---
    std::cout << "Dang ghi ket qua da sap xep ra file '" << fileOutput << "'..." << std::endl;
    if (ghiFileCSV(fileOutput, danhSachSV)) {
        std::cout << "Ghi file thanh cong!" << std::endl;
    } else {
        std::cerr << "Ghi file that bai." << std::endl;
    }

    return 0;
}