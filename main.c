#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @struct LogNode
 * @brief Syslog kayıtlarını tutan Çift Bağlı Liste düğüm yapısı.
 * * Neden Çift Bağlı Liste?
 * Loglar kronolojik sırayla eklenir. Hem en yeni loglara (sondan başa)
 * hem de en eski loglara (baştan sona) hızlı erişim sağlar.
 */
typedef struct LogNode {
    int id;                 // Log ID
    char timestamp[32];     // Zaman damgası
    char level[10];         // Log seviyesi (INFO, ERROR, DEBUG)
    char message[256];      // Log mesajı
    struct LogNode* next;   // Sonraki düğüm
    struct LogNode* prev;   // Önceki düğüm
} LogNode;

// Liste başı ve sonu takibi için global işaretçiler
LogNode* head = NULL;
LogNode* tail = NULL;

/**
 * @brief Yeni bir syslog kaydı ekler.
 * @param level Logun kritiklik seviyesi
 * @param msg Log mesaj içeriği
 */
void add_log(const char* level, const char* msg) {
    static int current_id = 1;
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));

    // Verileri düğüme kopyala
    newNode->id = current_id++;
    strcpy(newNode->level, level);
    strcpy(newNode->message, msg);

    // Zaman damgasını al
    time_t now = time(NULL);
    strftime(newNode->timestamp, 32, "%Y-%m-%d %H:%M:%S", localtime(&now));

    newNode->next = NULL;

    // Liste boşsa
    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
        tail = newNode;
    } else {
        // Çift bağlı liste mantığı: Sona ekle
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    printf("[Sistem]: Yeni log eklendi (ID: %d)\n", newNode->id);
}

/**
 * @brief Logları baştan sona (eskiden yeniye) listeler.
 */
void display_logs_forward() {
    LogNode* current = head;
    printf("\n--- SYSLOG KAYITLARI (ESKIDEN YENIYE) ---\n");
    while (current != NULL) {
        printf("[%s] %s | %s: %s\n", current->timestamp, current->level, "MSG", current->message);
        current = current->next;
    }
}

/**
 * @brief Logları sondan başa (yeniden eskiye) listeler.
 * Bu özellik sistem yöneticileri için en güncel hataları görmek adına kritiktir.
 */
void display_logs_backward() {
    LogNode* current = tail;
    printf("\n--- SYSLOG KAYITLARI (EN GUNCEL) ---\n");
    while (current != NULL) {
        printf("[%s] %s | %s: %s\n", current->timestamp, current->level, "MSG", current->message);
        current = current->prev;
    }
}

int main() {
    // Örnek log verileri oluşturma
    add_log("INFO", "Sistem baslatildi.");
    add_log("DEBUG", "Kernel modulleri yukleniyor...");
    add_log("ERROR", "Disk alani kritik seviyede!");
    add_log("INFO", "Kullanici giris yapti: admin");

    // Listeleme fonksiyonlarını çağır
    display_logs_forward();
    display_logs_backward();

    return 0;
}