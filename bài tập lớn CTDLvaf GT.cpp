#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MonHoc {
    char ten[30];
    int tinChi;
};

struct Diem {
    char maSV[15];
    char maMon[15];
    double diemSo;
};

struct SinhVien {
    char maSV[15];
    char hoTen[30];
    double toan, ly, anh, ctdl;
    double diemTB;
};

struct Node {
    struct SinhVien data;
    struct Node* next;
    struct Node* prev;
};

struct DanhSach {
    struct Node* head;
    struct Node* tail;
};

// ----------------- HÀM KH?I T?O -----------------
void khoiTao(struct DanhSach* ds) {
    ds->head = NULL;
    ds->tail = NULL;
}

struct Node* taoNode(struct SinhVien sv) {
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));
    p->data = sv;
    p->next = p->prev = NULL;
    return p;
}

void themCuoi(struct DanhSach* ds, struct SinhVien sv) {
    struct Node* p = taoNode(sv);
    if (ds->head == NULL)
        ds->head = ds->tail = p;
    else {
        ds->tail->next = p;
        p->prev = ds->tail;
        ds->tail = p;
    }
}

// ----------------- NH?P & XU?T -----------------
void nhapDanhSach(struct DanhSach* ds) {
    while (1) {
        struct SinhVien sv;
        printf("\nNhap ten sinh vien (nhap '$' de dung): ");
        fflush(stdin);
        gets(sv.hoTen);
        if (strcmp(sv.hoTen, "$") == 0)
            break;
        printf("Nhap ma sinh vien: ");
        gets(sv.maSV);
        printf("Nhap diem Toan: "); scanf("%lf", &sv.toan);
        printf("Nhap diem Ly: "); scanf("%lf", &sv.ly);
        printf("Nhap diem Tieng Anh: "); scanf("%lf", &sv.anh);
        printf("Nhap diem CTDL&GT: "); scanf("%lf", &sv.ctdl);
        getchar(); // b? Enter

        sv.diemTB = (sv.toan + sv.ly + sv.anh + sv.ctdl) / 4.0;
        themCuoi(ds, sv);
    }
}

void xuatDanhSach(struct DanhSach ds) {
    struct Node* p = ds.head;
    printf("\n%-10s %-20s %-8s %-8s %-8s %-8s %-8s\n", "MaSV", "HoTen", "Toan", "Ly", "Anh", "CTDL", "DTB");
    while (p != NULL) {
        printf("%-10s %-20s %-8.2lf %-8.2lf %-8.2lf %-8.2lf %-8.2lf\n",
               p->data.maSV, p->data.hoTen, p->data.toan, p->data.ly,
               p->data.anh, p->data.ctdl, p->data.diemTB);
        p = p->next;
    }
}

// ----------------- 18.2: S?P X?P THEO TOÁN -----------------
void sapXepTheoToan(struct DanhSach* ds) {
    struct Node *i, *j;
    for (i = ds->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data.toan > j->data.toan) {
                struct SinhVien temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// ----------------- 18.3: S?P X?P THEO ÐI?M TB -----------------
void sapXepTheoDTB(struct DanhSach* ds) {
    struct Node *i, *j;
    for (i = ds->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data.diemTB > j->data.diemTB) {
                struct SinhVien temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// ----------------- 18.4: T?M MAX / MIN -----------------
void timMaxMin(struct DanhSach ds) {
    if (ds.head == NULL) return;
    struct Node* max = ds.head;
    struct Node* min = ds.head;
    struct Node* p;
    for (p = ds.head; p != NULL; p = p->next) {
        if (p->data.diemTB > max->data.diemTB) max = p;
        if (p->data.diemTB < min->data.diemTB) min = p;
    }
    printf("\n== Sinh vien co DTB cao nhat ==\n");
    printf("%s - %s (%.2lf)\n", max->data.maSV, max->data.hoTen, max->data.diemTB);
    printf("\n== Sinh vien co DTB thap nhat ==\n");
    printf("%s - %s (%.2lf)\n", min->data.maSV, min->data.hoTen, min->data.diemTB);
}

// ----------------- 18.5: XU?T THEO X?P LO?I -----------------
char xepLoai(double dtb) {
    if (dtb >= 8.5) return 'A';
    else if (dtb >= 7.0) return 'B';
    else if (dtb >= 5.5) return 'C';
    else if (dtb >= 4.0) return 'D';
    else return 'F';
}

void xuatTheoLoai(struct DanhSach ds, char loai) {
    struct Node* p = ds.head;
    printf("\n== Danh sach sinh vien loai %c ==\n", loai);
    while (p != NULL) {
        if (xepLoai(p->data.diemTB) == loai) {
            printf("%s - %s (DTB: %.2lf)\n", p->data.maSV, p->data.hoTen, p->data.diemTB);
        }
        p = p->next;
    }
}

// ----------------- MAIN -----------------
int main() {
    struct DanhSach ds;
    khoiTao(&ds);
    int chon;
    char loai;

    while (1) {
        printf("\n===== MENU =====");
        printf("\n1. Nhap danh sach sinh vien");
        printf("\n2. Xuat danh sach");
        printf("\n3. Sap xep theo diem Toan");
        printf("\n4. Sap xep theo diem trung binh");
        printf("\n5. Tim sinh vien co DTB Max/Min");
        printf("\n6. Xuat sinh vien theo xep loai (A/B/C/D/F)");
        printf("\n0. Thoat");
        printf("\nChon: ");
        scanf("%d", &chon);
        getchar();

        switch (chon) {
        case 1:
            nhapDanhSach(&ds);
            break;
        case 2:
            xuatDanhSach(ds);
            break;
        case 3:
            sapXepTheoToan(&ds);
            printf("\nDa sap xep theo diem Toan.\n");
            break;
        case 4:
            sapXepTheoDTB(&ds);
            printf("\nDa sap xep theo diem trung binh.\n");
            break;
        case 5:
            timMaxMin(ds);
            break;
        case 6:
            printf("Nhap loai (A/B/C/D/F): ");
            scanf("%c", &loai);
            xuatTheoLoai(ds, loai);
            break;
        case 0:
            printf("\nThoat chuong trinh.\n");
            return 0;
        default:
            printf("\nLua chon khong hop le!\n");
        }
    }
}

