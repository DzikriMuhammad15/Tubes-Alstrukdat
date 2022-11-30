#include "console.h"


void start(ArrayDin *arr){
    // memasukkan 5 permainan utama ke dalam list game
    Load(arr, "../data/config.txt");
    printf("File konfigurasi sistem berhasil dibaca. BNMO berhasil dijalankan.\n");
}

////LOAD

void saveGame(ArrayDin l, FILE *file){
    // Prosedur menulis list dari game, baik history ataupun keseluruhan permainan kedalam suatu file txt

    // KAMUS LOKAL
    int ctr, i;
    char *judulGame;

    // ALGOROTMA
    ctr = 1;
    i = 0;
    fprintf(file, "%d\n", l.Neff); // jumalah gamenya
    while(ctr <= l.Neff-1){
        judulGame = l.A[i];
        fprintf(file, "%s\n", judulGame);
        ctr++;
        i++;
    }
    judulGame = l.A[i];
    fprintf(file, "%s", judulGame);
}

void save(char *namaFile, ArrayDin arr, TabMap arrmapsb){
    //fungsi melakukan save terhadap state dari permainan yang terkandung dalam array
    // dan menyimpannya dalam sebuah file konfigurasi txt
    // jika file sudah ada, maka akan ditanya konfirmasi untuk menimpa file yang sudah ada
    // KAMUS LOKAL
    FILE *fileOutput;

    char path[100]= "../data/";

    int i = 8;
    while (*namaFile != '\0')
    {
        path[i] = *namaFile;
        i++;
        *namaFile++;
    }

    // ALGORITMA
    fileOutput = fopen((path), "w");
    saveGame(arr, fileOutput);
    int j;
    for (j = 0 ; j < NbElmtArrMap(arrmapsb)-1 ; j++){
        SAVEFILESB(arrmapsb.TIMap[j],fileOutput);
        fprintf(fileOutput,"\n");
    }
    SAVEFILESB(arrmapsb.TIMap[j],fileOutput);
    fclose(fileOutput);
    printf("Save file berhasil disimpan\n");
}

void CreateGame(ArrayDin *array){
    char* gamestring;
    int i = 0;
    boolean found = false;
    printf("Masukkan game yang ingin ditambahkan : ");  
    gamestring = scaninput();
    while(found == false && i < (*array).Neff){
        if(IsStrEq(gamestring, array->A[i])){
            found = true;
        }
        i++;
    }
    if (found == true){
        printf("Game sudah ada di sistem\n");
    }
    else{
        InsertLast(array,gamestring);
        printf("Game berhasil ditambahkan.\n");
    }
}

void ListGame(ArrayDin *array){
    printf("Berikut adalah daftar game yang tersedia\n");
    int i;
    for(i = 0 ; i <= (Length(*array)-1) ; i++ ){
        printf("%d. %s\n",(i+1),array->A[i]);
    }

}

void DeleteGame(ArrayDin *array, Queue *queue){
    char* nomor;
    int intnomor,i;
    printf("Masukkan nomor game yang akan dihapus: ");
    nomor = scaninput();
    intnomor = atoi(nomor);
    if(intnomor == 1 || intnomor == 2 || intnomor == 3 || intnomor == 4 || intnomor == 5){
        printf("Game gagal dihapus!\n");
    }
    /// ELSE IF KALO ADA DI QUEUE
    else{
        i = 0;
        while((i+1) != intnomor){
            i++;
        }
        if(!isEmptyQueue(*queue)){
            int z = IDX_HEAD(*queue);
            boolean sama = false;
            while(z <= IDX_TAIL(*queue)){
                if(IsStrEq(array->A[i],(*queue).buffer[z])){
                    sama = true;
                }
                z++;
            }

            if (sama == true){
                printf("Game gagal dihapus!\n");
            }
            else{
                DeleteAt(array, i);
                printf("Game berhasil dihapus\n");
            }

        }
        else{
            DeleteAt(array, i);
            printf("Game berhasil dihapus\n");
        }
    }
}

void QueueGame(ArrayDin *array, Queue *q){
	int i, nomorint; 
	char* nomorgame;
    Word num;
	ListGame(array);
	printf("Nomor game yang mau ditambahkan ke antrian : ");
	nomorgame = scaninput();
	nomorint = atoi(nomorgame);
	if (nomorint >= 1 && nomorint <= (Length(*array))){
		enqueue(q, (*array).A[nomorint-1]);
		printf("Game berhasil ditambahkan kedalam daftar antrian.\n");
	}
	else {
		printf("Nomor permainan tidak valid, silahkan masukkan nomor game pada list\n");
    }

}


void PlayGame(Queue *q)
{
    ElType val;
    if(!isEmptyQueue(*q))    //kalau queue game ada isinya maka,
    {
        printf("Berikut adalah daftar Game-mu\n");  //print q dulu

        int i,index = 1;
        for (i = IDX_HEAD(*q); i <= IDX_TAIL(*q); i++)
        {
            printf("%d. %s\n", index , (*q).buffer[i]);
            index++;
        }

        char *R = "RNG";
        char *DinDash = "DINER DASH";
        char *TOH = "TOH";
        char *Hangman = "HANGMAN";
        char *SOM = "SNAKE ON METEOR";
        /**char *DIE = "DINOSAUR IN EARTH";
        char *RISE = "RISEWOMAN";
        char *ET = "EIFFEL TOWER";**/

        if (IsStrEq(HEAD(*q), R)){
            printf("Loading %s ...\n", HEAD(*q));
            dequeue(q,&val);
            Donat();
            RNG();  

        }
        else if (IsStrEq(HEAD(*q), DinDash)){
            printf("Loading %s ...\n", HEAD(*q));
            dequeue(q,&val);
            Donat();
            dinerdash();  
        }
        else if (IsStrEq(HEAD(*q), TOH)){
            printf("Loading %s ...\n", HEAD(*q));
            dequeue(q,&val);
            Donat();
            towerofhanoi();  
        }

        /**else if (IsStrEq(HEAD(*q), DIE) || IsStrEq(HEAD(*q), RISE) || IsStrEq(HEAD(*q), ET)){
            printf("Game %s masih dalam maintenance, belum dapat dimainkan. Silahkan pilih game lain.\n", HEAD(*q));
            dequeue(q,&val);
        }**/
        else if (IsStrEq(HEAD(*q), Hangman)){
            printf("Loading %s ...\n", HEAD(*q));
            dequeue(q,&val);
            Donat();
            ///hangman(); 
        }
        else if (IsStrEq(HEAD(*q), SOM)){
            printf("Loading %s ...\n", HEAD(*q));
            dequeue(q,&val);
            Donat();
            ///snake();
        } 
        else{
            srand(time(NULL));
            int score = rand() % 100 + 1;
            printf("Loading %s ...\n", HEAD(*q));
            printf("Score : %d\n",score);
            dequeue(q,&val);
        }
    }
    else    
    {
        printf("Belum ada game di QueueGame. Silahkan mengisi queue game terlebih dahulu\n");
    }
   
}


void SkipGame(Queue *q, int n){
    // I.S. queue game terdefinisi dan mungkin kosong
    // F.S. melakukan dequeue n element q pertama dan menjalankan game ke n+1
    //      jika n lebih besar dari jumlah game dalam queue game, maka akan memberikan pesan kesalahan

    // KAMUS LOKAL
    ElType game;
    int panjang, i;

    // ALGORITMA
    panjang = length(*q);
    if(!isEmptyQueue(*q)){
        // kasus queue game tidak kosong
        if(n < panjang){
            // kasus menjalankan game ke n+1
            for(i = 1 ; i <= n; i++){
                dequeue(q, &game);
            }
            // nama game disini adalah nama game yang akan dimainkan
            PlayGame(q);
        }
        else if(n == panjang){
            // kasus game tidak dimainkan karena semua game dalam queue game tepat sudah didequeue
            for(i = 1 ; i <= n ; i++){
                dequeue(q, &game);
            }
            printf("Tidak ada permainan lagi dalam daftar game-mu.\n");
        }
        else{
            for(i = 1 ; i <= panjang ; i++){
                dequeue(q, &game);
            }
            printf("Tidak ada permainan lagi dalam daftar game-mu.\n");
        }
    }
    else{
        // kasus queue game kosong
        printf("Queue masih kosong, silahkan QUEUE GAME untuk menambahkan game ke dalam antrian\n");
    }
}


void quit(Queue *q){
    printf("Anda keluar dari game BNMO\n");
    printf("Bye bye ...\n");
    CreateQueue(q);
}


void help()
{
    printf("---------- HELP ----------\n");
    printf("Berikut Pilihan Command yang Tersedia \n");
    printf("1. START : Membaca file konfigurasi sistem agar BNMO dapat berjalan\n");
    printf("2. LOAD : Membaca save file <filename> yang berisi list game yang dapat dimainkan, histori dan scoreboard game\n");
    printf("3. SAVE : Menyimpan state game pemain saat ini ke dalam suatu file\n");
    printf("4. CREATEGAME : Menambahkan game baru pada daftar game\n");
    printf("5. LISTGAME : Menampilkan daftar game yang disediakan oleh sistem\n");
    printf("6. DELETEGAME : Menghapus sebuah game dari daftar game\n");
    printf("7. QUEUEGAME : Mendaftarkan permainan kedalam list\n");
    printf("8. PLAYGAME : Memainkan sebuah permainan yang berada pada urutan paling atas\n");
    printf("9. SKIPGAME : Melewatkan permainan sebanyak n\n");
    printf("10. SCOREBOARD : Melihat nama dan skor untuk semua game\n");
    printf("11. RESET SCOREBOARD : melakukan reset terhadap scoreboard permainan\n");
    printf("12. HISTORY : Melihat permainan apa saja yang telah dimainkan dari data yang sudah ada\n");
    printf("13. RESET HISTORY : Menghapus semua history permainan yang dimainkan\n");
    printf("14. QUIT : Keluar dari Program\n");
    printf("15. HELP : Bantuan command-command pada BNMO\n");
}


void CommandLain(){
    printf("Command tidak dikenali, silahkan masukkan command yang valid.\n");
}

void Load(ArrayDin *arraygame, char *namafile){
    STARTLOAD(namafile);
    int jumlahgame = currentChar - '0';
    printf("%d\n",jumlahgame);
    int i,j;
    ADVWORDLOAD();
    for (i=0;i<jumlahgame;i++){
        ADVWORDLOAD();
        char *namagame;
        namagame = (char *)malloc(currentWord.length * sizeof (char));
        for (j = 0; j < currentWord.length ; j++){
            *(namagame + j) = currentWord.contents[j];
        }
        *(namagame + currentWord.length) = '\0';
        printf("%s\n" , namagame);
        arraygame->A[i] = namagame;
    }
    (*arraygame).Neff = jumlahgame;
}

void  *my_memset(void *b, int c, int len)
{
  int           i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}

void Donat(){
    float A = 0, B = 0;
    float i, j;
    int time;
    int k;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");
    for(time = 0; time < 50; time++) {
        my_memset(&b,32,1760);
        my_memset(&z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
    }
}

void SAVESCOREBOARD (Map *mapGame, int skor){ // ini tapi belum masuk ke file konfigurasi
    printf("Nama: ");
    char *nama;
    nama = scaninput();
    while (IsMemberMap(*mapGame,nama)){
        printf("Nama sudah terpakai silahkan pilih nama lain\n");
        printf("Nama: ");
        nama = scaninput();
    }
    InsertMap(mapGame,nama,skor);
}

void PrintScore (Map scoreboard, char *nama){
    printf("**** \t\tSCOREBOARD GAME %s\t\t ****\n",nama);
    printf("| NAMA\t\t\t\t | SKOR \t\t\t |\n");
    printf("|----------------------------------------------------------------|\n");
    Map temp;
    temp = CopyMap(&scoreboard);
    int totalskor = scoreboard.Count;
    int strmax;
    strmax = lenmax(&scoreboard);
    if (totalskor > 0 && strmax < 6){
        for (int i = 0; i<totalskor;i++){
            int idxmax;
            idxmax = IMAX(&temp);
            printf("| %s\t\t\t\t | %d \t\t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
            DeleteMap(&temp,temp.Elements[idxmax].Key);
        }
    }
    else if(totalskor > 0 && strmax >= 6){
        for (int i = 0; i<totalskor;i++){
                int idxmax;
                idxmax = IMAX(&temp);
                if (LengthStr(temp.Elements[idxmax].Key) < 6){
                    if(LengthStr(numToString(temp.Elements[idxmax].Value))>3){
                        printf("| %s\t\t\t\t | %d \t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
                        DeleteMap(&temp,temp.Elements[idxmax].Key);
                    }
                    else{
                        printf("| %s\t\t\t\t | %d \t\t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
                        DeleteMap(&temp,temp.Elements[idxmax].Key);
                    }
                }
                else if(LengthStr(temp.Elements[idxmax].Key) > 13 ){
                    if(LengthStr(numToString(temp.Elements[idxmax].Value))>3){
                        printf("| %s\t\t | %d \t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
                        DeleteMap(&temp,temp.Elements[idxmax].Key);
                    }
                    else{
                        printf("| %s\t\t | %d \t\t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
                        DeleteMap(&temp,temp.Elements[idxmax].Key);
                    }
                }
                else{
                    if(LengthStr(numToString(temp.Elements[idxmax].Value))>3){
                        printf("| %s\t\t\t | %d \t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
                        DeleteMap(&temp,temp.Elements[idxmax].Key);
                    }
                    else{
                        printf("| %s\t\t\t | %d \t\t\t\t |\n",temp.Elements[idxmax].Key,temp.Elements[idxmax].Value);
                        DeleteMap(&temp,temp.Elements[idxmax].Key);
                    }
                }
            }
    }
    else{
        printf("---\t\t    SCOREBOARD KOSONG\t\t       ---\n");
    }
    printf("\n");
}

void SCOREBOARD (TabMap arrscore, ArrayDin listgame){
    // LOOPING DARI PRINTSCORE
    for (int i=0;i<NbElmtArrMap(arrscore);i++){
        PrintScore(arrscore.TIMap[i],listgame.A[i]);
    }
}




void SAVEFILESB (Map scoreboard, FILE *txt){
    fprintf(txt,"%s",numToString(scoreboard.Count));
    Map temp;
    temp = CopyMap(&scoreboard);
    int idxmax;
    idxmax = IMAX(&scoreboard);
    for (int i = 0; i<scoreboard.Count;i++){
        fprintf(txt,"\n%s %s",temp.Elements[idxmax].Key,numToString(temp.Elements[idxmax].Value));
        DeleteMap(&scoreboard,temp.Elements[idxmax].Key);
    }
}

void RESETSCORE(TabMap *TabSB, ArrayDin *listgame)
{   char* jawab;
    char* ya = "YA";
    char* tdk = "TIDAK";
    int nomorint;
    char* nomorgame;

    //Print daftar list game
    printf("DAFTAR SCOREBOARD : \n");  
    printf("0. ALL\n");
    int index = 1;
    int i;
    int j;
    int k;
    Map *sb;
    boolean found = false;
    for(i = 0 ; i <= (Length(*listgame)-1) ; i++ ){
        printf("%d. %s\n",(i+1),listgame->A[i]);
    }
    // Masukkan input scoreboard yang ingin dihapus
    printf("SCOREBOARD YANG INGIN DIHAPUS : ");
    nomorgame = scaninput();
    nomorint = atoi(nomorgame);
    printf("\n");
    if (nomorint == 0){
        printf("APAKAH KAMU YAKIN INGIN MELAKUKAN RESET SCOREBOARD ALL (YA/TIDAK)? ");
        jawab = scaninput();
        if(IsStrEq(ya,jawab)){
            for (j = 0; j < (NbElmtArrMap(*TabSB)); j++){
                *sb = GetElmtArrMap(*TabSB, j);
                CreateEmptyMap(sb);
            }
            printf("\n");
            printf("Scoreboard berhasil di-reset.");
        }
        else{
            printf("Scoreboard gagal di-reset.");
        }    
    }
    else if (nomorint >=1){
        printf("APAKAH KAMU YAKIN INGIN MELAKUKAN RESET SCOREBOARD GAME %s (YA/TIDAK)? ", listgame->A[nomorint-1]);
        jawab = scaninput();
        if(IsStrEq(ya,jawab)){
            for(k = 0; k < (NbElmtArrMap(*TabSB)); k++){
                if (nomorint-1 == k){
                    *sb = GetElmtArrMap(*TabSB, k);
                    CreateEmptyMap(sb);
                    found = true;
                }
                if (!found){
                    printf("INPUT TIDAK TERDAPAT DI SCOREBOARD\n");
                }
            }
        }
        else{
            printf("Scoreboard gagal di-reset.\n");
        }
    }
    else{
        printf("INPUT TIDAK VALID\n");
    }
}
void RESETHISTORY(Stack* Hist){
	char* ya = "YA";
	char* tidak = "TIDAK";
    char* jawab;
	printf("APAKAH KAMU YAKIN INGIN MELAKUKAN RESET HISTORY? (YA/TIDAK) ");
	jawab = scaninput();
	if(IsStrEq(ya, jawab)){
		CreateEmpty(Hist);
		printf("\n");
		printf("Histori berhasil di-reset.");
	}
	else if(IsStrEq(tidak, jawab)){
		printf("\n");
		printf("Histori tidak jadi di-reset. Berikut adalah daftar Game yang telah dimainkan\n");
		// HISTORY();
	}
	else {
		printf("MASUKKAN INPUT YANG VALID!");
	}
}