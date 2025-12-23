#include <stdio.h>
#include <string.h>

// biodata artist
typedef struct {
    char namaArtist[50];
    char namaLagu[50];
    char genre[30];
} Artist; 

// kategori roasting
typedef enum {
    ROAST_NORMIE,
    ROAST_TRYHARD,
    ROAST_DELUSIONAL,
    ROAST_EDGY,
    ROAST_PLAYER,
    ROAST_STARBOY,
    ROAST_PERFORMATIVE,
    ROAST_SKENA,
    ROAST_SAD,
    ROAST_COUNT
} RoastType;

typedef struct {
    int point[ROAST_COUNT];
} RoastScore;

// dipake khusus di leaderboard
typedef struct {
    char nama[50];
    int count;
} Counter;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void toLowerCase(char str[]) {
    int i;
    for (i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

// modul input
void inputDanSimpan() {
    FILE *fp;
    Artist a;
    int pilihanGenre;
    int jumlah;
    int i;
    

    fp = fopen("artist.dat", "ab");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    
    

    printf("\nMasukkan jumlah lagu yang ingin diinput: ");
    scanf("%d", &jumlah);
    clearBuffer(); 
	
	

    for (i = 0; i < jumlah; i++) {
    	
    	
        printf("\n=== Lagu ke-%d ===\n", i + 1);
        // yang di input adalah nama lagu
        printf("Nama lagu: ");
		fgets(a.namaLagu, sizeof(a.namaLagu), stdin);
		a.namaLagu[strcspn(a.namaLagu, "\n")] = '\0';
		toLowerCase(a.namaLagu);

	// yang di input adalah nama artist
        printf("Nama artist (wajib lowercase!!)): ");
		fgets(a.namaArtist, sizeof(a.namaArtist), stdin);
		a.namaArtist[strcspn(a.namaArtist, "\n")] = '\0';
		toLowerCase(a.namaArtist);


	//opsi milih genre, yand di input adalah nomernya
        printf("\nPilih genre utama artist:\n");
        printf("1. Pop\n");
        printf("2. Rap / Hip-Hop\n");
        printf("3. Rock / Punk\n");
        printf("4. Metal / Goth\n");
        printf("5. EDM / Electronic\n");
        printf("6. Jazz / Blues\n");
        printf("7. Indie / Alternative\n");
        printf("8. RnB / Soul\n");
        printf("9. OST / Soundtrack\n");
        printf("10. Lainnya\n");
        printf("Pilihan (1-10): ");
        scanf("%d", &pilihanGenre);
         clearBuffer(); 

//  switch pilihan genre
switch (pilihanGenre) {
            case 1: strcpy(a.genre, "Pop"); break;
            case 2: strcpy(a.genre, "Rap"); break;
            case 3: strcpy(a.genre, "Rock"); break;
            case 4: strcpy(a.genre, "Metal"); break;
            case 5: strcpy(a.genre, "EDM"); break;
            case 6: strcpy(a.genre, "Jazz"); break;
            case 7: strcpy(a.genre, "Indie"); break;
            case 8: strcpy(a.genre, "RnB"); break;
            case 9: strcpy(a.genre, "OST"); break;
            case 10: strcpy(a.genre, "Lainnya"); break;
            default:
                printf("Genre tidak valid, ulangi input.\n");
                i--;
                continue;
        }

        fwrite(&a, sizeof(Artist), 1, fp);
    }	

    fclose(fp);
    printf("\nData berhasil disimpan.\n");
    
    printf("\nTekan ENTER untuk kembali ke menu...");
    clearBuffer();
    getchar();
}

// menu lihat leaderboard genre / artist
// mode = 1 ? leaderboard genre
// mode = 2 ? leaderboard artist
void leaderboard(int mode) {
//simpan nama artist di file
    FILE *fp = fopen("artist.dat", "rb");
    if (!fp) { printf("Belum ada data.\n"); return; }
    Artist a;
    Counter list[200];
    int total = 0, i, j;
    while (fread(&a, sizeof(Artist), 1, fp)) {
        char *target = (mode == 1) ? a.genre : a.namaArtist;
        int found = -1;
        for (i = 0; i < total; i++) {
            if (strcmp(list[i].nama, target) == 0) { found = i; break; }
        }
        if (found != -1) list[found].count++;
        else { strcpy(list[total].nama, target); list[total].count = 1; total++; }
    }
    fclose(fp);
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (list[j].count < list[j+1].count) {
                Counter temp = list[j]; list[j] = list[j+1]; list[j+1] = temp;
            }
        }
    }
    printf("\n=== LEADERBOARD %s ===\n", (mode == 1) ? "GENRE" : "ARTIST");
    for (i = 0; i < total; i++) printf("%d. %s : %d lagu\n", i+1, list[i].nama, list[i].count);
    printf("========================\n\nTekan ENTER...");
    getchar();
}

// menentukan roast berdasarkan nama artist yg dimasukkan
RoastType artistToRoast(char nama[]) {
    if (strcmp(nama, "taylor swift") == 0) return ROAST_SAD;
    if (strcmp(nama, "hindia") == 0) return ROAST_SAD;
    if (strcmp(nama, "billie eilish") == 0) return ROAST_SAD;
    if (strcmp(nama, "juicy lucy") == 0) return ROAST_SAD;
    if (strcmp(nama, "niki") == 0) return ROAST_SAD;
    if (strcmp(nama, "sza") == 0) return ROAST_SAD;

    if (strcmp(nama, "sabrina carpenter") == 0) return ROAST_PERFORMATIVE;
    if (strcmp(nama, "ariana grande") == 0) return ROAST_PERFORMATIVE;
    if (strcmp(nama, "illit") == 0) return ROAST_PERFORMATIVE;

    if (strcmp(nama, "the weeknd") == 0) return ROAST_PLAYER;
    if (strcmp(nama, "bruno mars") == 0) return ROAST_PLAYER;

    if (strcmp(nama, "blackpink") == 0) return ROAST_STARBOY;
    if (strcmp(nama, "le sserafim") == 0) return ROAST_STARBOY;

    if (strcmp(nama, "tyler, the creator") == 0) return ROAST_SKENA;
    if (strcmp(nama, "arctic monkeys") == 0) return ROAST_SKENA;

    if (strcmp(nama, "sheila on 7") == 0) return ROAST_NORMIE;

    return ROAST_COUNT;
}

// Tipe-tipe roastingannya
RoastType genreToRoast(char genre[]) {
    if (strcmp(genre, "Pop") == 0) return ROAST_NORMIE;
    if (strcmp(genre, "Rap") == 0) return ROAST_PLAYER;
    if (strcmp(genre, "Rock") == 0) return ROAST_EDGY;
    if (strcmp(genre, "Metal") == 0) return ROAST_EDGY;
    if (strcmp(genre, "EDM") == 0) return ROAST_STARBOY;
    if (strcmp(genre, "Jazz") == 0) return ROAST_SKENA;
    if (strcmp(genre, "Indie") == 0) return ROAST_SAD;
    if (strcmp(genre, "OST") == 0) return ROAST_DELUSIONAL;

    return ROAST_NORMIE;
}

// hitung roast type pake sistem poin

void hitungRoastDariFile(RoastScore *score) {
    FILE *fp;
    Artist a;
    RoastType r;
    int i;

    for (i = 0; i < ROAST_COUNT; i++)
        score->point[i] = 0;

    fp = fopen("artist.dat", "rb");
    if (fp == NULL) {
        printf("Belum ada data artist.\n");
        return;
    }

    while (fread(&a, sizeof(Artist), 1, fp)) {
		r = artistToRoast(a.namaArtist);
        if (r == ROAST_COUNT)
            r = genreToRoast(a.genre);

        score->point[r]++;
    }

    fclose(fp);
}


RoastType roastTerbesar(RoastScore score) {
    int i, max = 0;
    for (i = 1; i < ROAST_COUNT; i++) {
        if (score.point[i] > score.point[max])
            max = i;
    }
    return max;
}

// function tampilkan roastingannya

void tampilkanRoast(RoastType r) {
    switch (r) {
        case ROAST_NORMIE:
            printf("Siapa lagi kalo bukan pendengar setia billboard chart 100...\n");
            break;
        case ROAST_SAD:
            printf("Siapa lagi yang playlistnya kayak gini kalo bukan si paling sadboy/sadgirl. Sesulit apa si sampe kalian gamon?\n");
            break;
        case ROAST_DELUSIONAL:
            printf("Stop fanatik dan fokus ke realita. Meskipun musik itu satu-satunya hal yang bikin kamu oke, tapi gak gitu juga ya…\n");
            break;
        case ROAST_PERFORMATIVE:
            printf("Playlist kamu isinya kek gini cuma buat keliatan aesthetic doang, iya kan?\n");
            break;
        case ROAST_PLAYER:
            printf("Katanya cuma suka beatnya, padahal kamu itu sesuai liriknya yang red flag.\n");
            break;
        case ROAST_SKENA:
            printf("Kamu gak kalcer, kamu cuma nolep dan sering doomscrolling.\n");
            break;
        case ROAST_EDGY:
            printf("CZ TONIGHT WILL BE THE NIGHT THAT I'LL DIE FOR YOUUU DASAR EMO.\n");
            break;
        case ROAST_STARBOY:
            printf("BRODDIE IS NOT A STARBOY. LU HIDUP DI PULAU JAWA TAU!!!.\n");
            break;
        default:
            printf("Baca intruksinya baik-baik, gak susah kan.\n");
    }
}


void roastSeleraSaya() {
    RoastScore score;
    RoastType hasil;

    hitungRoastDariFile(&score);
    hasil = roastTerbesar(score);

    printf("\n=== HASIL ROAST ===\n");
    tampilkanRoast(hasil);
}

// menu lihat semua data
void lihatSemuaData() {
    FILE *fp;
    Artist a;
    int nomor = 1;

    fp = fopen("artist.dat", "rb");
    if (!fp) {
        printf("Belum ada data.\n");
        printf("Tekan ENTER untuk kembali ke menu...");
        getchar();
        return;
    }

    printf("\n=== SEMUA DATA LAGU ===\n");
    
    while (fread(&a, sizeof(Artist), 1, fp)) {
        printf("%d. %s - %s [%s]\n", nomor, a.namaArtist, a.namaLagu, a.genre);
        nomor++;
    }

    fclose(fp);
    
    if (nomor == 1) {
        printf("Belum ada data tersimpan.\n");
    } else {
        printf("\nTotal: %d lagu\n", nomor - 1);
    }
    
    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar();
}

void searchArtist() {
    FILE *fp;
    Artist a;
    char cari[50];
    int jumlahLagu = 0;

    fp = fopen("artist.dat", "rb");
    if (!fp) {
        printf("Belum ada data.\n");
        printf("Tekan ENTER untuk kembali ke menu...");
        getchar();
        return;
    }

    // Clear buffer dulu sebelum input
    clearBuffer();
    
    printf("Masukkan nama artist: ");
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = '\0';
    toLowerCase(cari);

    printf("\n=== HASIL PENCARIAN ===\n");
    
    while (fread(&a, sizeof(Artist), 1, fp)) {
        if (strcmp(a.namaArtist, cari) == 0) {
            if (jumlahLagu == 0)
                printf("Artist: %s\n\n", a.namaArtist);

            printf("%d. %s (%s)\n", jumlahLagu + 1, a.namaLagu, a.genre);
            jumlahLagu++;
        }
    }

    fclose(fp);

    if (jumlahLagu == 0) {
        printf("Artist '%s' tidak ditemukan.\n", cari);
    } else {
        printf("\nTotal lagu dari %s: %d\n", cari, jumlahLagu);
    }
    
    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar();
}
// simpan hasil roast di file
void simpanHasilRoast() {
    FILE *fp;
    RoastScore score;
    RoastType hasil;
    int i;

    hitungRoastDariFile(&score);
    hasil = roastTerbesar(score);

    fp = fopen("hasil_roast.txt", "w");
    if (fp == NULL) {
        printf("Gagal menyimpan hasil roast.\n");
        return;
    }

    fprintf(fp, "===== HASIL ANALISIS ROASTIFY =====\n\n");

    fprintf(fp, "Poin tiap kategori:\n");
    for (i = 0; i < ROAST_COUNT; i++) {
        fprintf(fp, "- Roast %d : %d poin\n", i, score.point[i]);
    }

    fprintf(fp, "\nRoast Dominan: %d\n", hasil);

    fclose(fp);

    printf("\nHasil roast berhasil disimpan ke file 'hasil_roast.txt'\n");
    printf("Tekan ENTER untuk kembali ke menu...");
    getchar();
}

// Fitur deteksi fake fan

void deteksiFakeFan() {
    FILE *fp;  //pointer file
    Artist a;
    char cari[50];
    int jumlahLagu = 0;
    
    fp = fopen("artist.dat", "rb");
    if (!fp) {
        printf("Belum ada data.\n");
        printf("\nTekan ENTER untuk kembali ke menu...");
        getchar();
        return;
    }
    
    clearBuffer();
    
    printf("\n=== DETEKSI FAKE FAN ===\n");
    printf("Masukkan nama artist favorit kamu: ");
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = '\0';
    toLowerCase(cari);
    
    // Hitung jumlah lagu dari artist tersebut
    while (fread(&a, sizeof(Artist), 1, fp)) {
        if (strcmp(a.namaArtist, cari) == 0) {
            jumlahLagu++;
        }
    }
    fclose(fp);
    
    printf("\n=== HASIL DETEKSI ===\n");
    printf("Kamu punya %d lagu dari '%s'\n\n", jumlahLagu, cari);
    
    // Deteksi Fake Fan bedasrakan jumlah lagu yang di input
    if (jumlahLagu == 0) {
        printf("100%% FAKE FAN DETECTED! ??\n");
        printf("Kamu bahkan gak tau satupun lagu dari artist ini. ??\n");
        printf("Jangan-jangan cuma tau nama doang? Hadeh ??\n");
    } else if (jumlahLagu < 3) {
        printf("FAKE FAN DETECTED! ??\n");
        printf("Cuma %d lagu? Pasti fake fan, baru denger sedikit lagunya di internet. ??\n", jumlahLagu);
        printf("Real fan mah minimal punya 3 lagu!\n");
    } else if (jumlahLagu < 5) {
        printf("CASUAL FAN ??\n");
        printf("Ya ini sih normalnya, tapi belum oke buat disebut real fan. ??\n");
        printf("Dengerin lebih banyak lagu artist yang tadi kamu input! ??\n");
    } else if (jumlahLagu < 10) {
        printf("REAL FAN! ?\n");
        printf("Oke deh, kamu emang bener-bener suka ni artist. ??\n");
        printf("Dari jumlah lagu yang  udah kamu masukin sih udah cukup solid! ??\n");
    } else {
        printf("SUPERFAN! ??\n");
        printf("WAH! %d lagu?? Artinya kamu udah hardcore fan! ??\n", jumlahLagu);
        printf("Respect banget buat dedikasi kamu! ??\n");
    }
    
    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar();
}

void keluarProgram() {
    printf("\nTerima kasih sudah pakai ROASTIFY!!\n");
    printf("Program dihentikan.\n");
}


int main() {
    int pilihan;

    do {
        printf("\n+--------------------------------------+\n");
        printf("|            ROASTIFY v1.0             |\n");
        printf("| Lets see how bad is your music taste |\n");
        printf("|--------------------------------------|\n");
        printf("| 1. Input Data Artist                 |\n");
        printf("| 2. Search Artist                     |\n");
        printf("| 3. Lihat Semua Data                  |\n");
        printf("| 4. Leaderboard Genre                 |\n");
        printf("| 5. Leaderboard Artist                |\n");
        printf("| 6. Roast Selera Saya                 |\n");
        printf("| 7. Simpan Data                       |\n");
        printf("| 8. Fake Fan Detector                 |\n");
        printf("| 9. Keluar                            |\n");
        printf("+--------------------------------------+\n");

        printf("Pilih menu > ");
        scanf("%d", &pilihan);
        clearBuffer();

        switch (pilihan) {
            case 1: //input nama lagu, artist, dan genre
                inputDanSimpan();
                break;
                
            case 2: // cari nama artist
   				searchArtist();
   				break;
   			
 			case 3:  // lihat semua data
   				lihatSemuaData();
   				break;

            case 4: //leaderboard genre
                leaderboard(1);
                break;

            case 5: //leaderboard artist
                leaderboard(2);
                break;

            case 6: //roasting selera musik kamu
                roastSeleraSaya();
                printf("\nTekan ENTER untuk kembali ke menu...");
                getchar();
                break;
                
            case 7: //simpan hasil roast kamu di file
            	simpanHasilRoast();
				break;
				
			case 8: //deteksi fake fan
				deteksiFakeFan();
   				break;
								
            case 9:  //keluar program
            	keluarProgram();
                printf("Keluar dari program...\n");
                break;

            default:
                printf("Menu belum tersedia.\n");
                printf("Tekan ENTER untuk lanjut...");
                getchar();
        }

    } while (pilihan != 9);

    return 0;
}
