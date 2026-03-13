# Linux Syslog Bilgilerinin Bağlı Liste İle Gösterilmesi

Bu proje, Linux işletim sistemindeki sistem günlüklerinin (syslog) çalışma mantığını anlamak ve bu verileri **Çift Bağlı Liste (Doubly Linked List)** veri yapısı kullanarak verimli bir şekilde yönetmek amacıyla geliştirilmiştir.

## Proje Hakkında
Sistem günlükleri (syslog), işletim sisteminde meydana gelen olayların (hata, bilgi, uyarı) kronolojik bir dökümüdür. Bu projede, verilerin dinamik olarak yönetilmesi ve özellikle sistem yöneticilerinin ihtiyaç duyduğu "en güncel loga hızlı erişim" senaryosunu gerçekleştirmek için çift bağlı liste yapısı tercih edilmiştir.

## Teknik Detaylar ve Tercih Sebebi
- **Veri Yapısı:** Çift Bağlı Liste (Doubly Linked List)
- **Tercih Sebebi:** Syslog kayıtları sürekli akan ve büyüyen verilerdir. Çift bağlı liste kullanarak:
  1. Veriler arasında hem ileri hem de geri yönde hareket edilebilir.
  2. Listenin sonuna (`tail`) eklenen bir işaretçi sayesinde, en güncel log kayıtlarına $O(1)$ zaman karmaşıklığı ile erişilebilir.
  3. Dinamik bellek yönetimi sayesinde sistem kaynakları verimli kullanılır.

## Yazılım Gereksinimleri
Uygulamayı derlemek ve çalıştırmak için sisteminizde bir C derleyicisinin (GCC) kurulu olması gerekmektedir.
- **macOS:** Xcode Command Line Tools
- **Linux:** build-essential paketi

## Kurulum ve Çalıştırma

1. Terminali açın.
2. Proje dosyalarının bulunduğu dizine gidin:
   ```bash
   cd /dosya/yolu/buraya
  
   gcc main.c -o syslog_app

   ./syslog_app
   
