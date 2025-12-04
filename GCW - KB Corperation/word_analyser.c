//text analyzer programme of KB Corperation
#include <stdio.h>
#include <string.h>//string functions
#include <ctype.h>//judge character type
#include <stdlib.h>//for rename function

#define UpLimit_WORDS 1000 
#define WORD_LONG 40 //max word length

// 1-1.load file,write words
int loadWords(const char *fileName, char words[][WORD_LONG]){//load words from file
    FILE *fp=fopen(fileName,"r");//file open,"r"read mode
    if(fp==NULL){          //error open
        printf("opened failed!\n");
        return 0;       //return！
    }
    char word[WORD_LONG];//judge type
    int count=0;//sum words
    while(fscanf(fp,"%39s",word)==1){//read word,stop by space
        //process words
        for(int i=0;word[i];i++){//traverse each character
            if (ispunct(word[i])!=0){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
                word[i]=0;// Punctuation mark as stop flag
                break;//exit loop
            }
            word[i]=tolower(word[i]);// become lowercase
        }if(strlen(word)>0){  //end with '\0',string lens>0，non-empty string
            strcpy(words[count],word);
            count++;
            if(count>=UpLimit_WORDS){//break limit
                printf("reach upLimit\n");
                break;
            }
        }
    }
    printf("Total words:%d\n", count);//output
    fclose(fp);//close file
    return count;//return value
}

// 1-2.count unique words
int countUniqueWords(char words[][WORD_LONG], int wordCount){
    char uniqueWords[UpLimit_WORDS][WORD_LONG];
    int uniqueCount=0;//calculate repeating word

    for(int i=0;i<wordCount;i++){//traverse all words
        int found=0;//record if found
        for(int j=0;j<uniqueCount;j++){
            if(strcmp(words[i],uniqueWords[j])==0){// compare every word
                found=1;//already found
                break;// find it & exit
            }
        }if(found==0){// if not , which is new word 
            strcpy(uniqueWords[uniqueCount], words[i]);//add to uniquewords
            uniqueCount++;// unique word +1
        }
    }
    return uniqueCount;
}

// 1-3.load stopwords.txt
int loadStopwords(char stopwords[][WORD_LONG]){
    FILE *fp=fopen("stopWords.txt","r");// open file
    if(fp==NULL){// if open failed
        printf("stopWords.txt open failed.\n");
        return 0;// return if fail
    }
    char word[WORD_LONG];
    int count=0;
    while(fscanf(fp,"%39s",word)==1&&count<UpLimit_WORDS){// set limit
        for(int i=0;word[i];i++){
            if(ispunct(word[i])!=0){// if is punctuation
                word[i]=0;     //='\0' clear
                break;
            }
            word[i]=tolower(word[i]);//become lowercase
        }if(strlen(word)>0) {//'\0', not empty string
            strcpy(stopwords[count], word);
            count++;// number +1
        }
    }
    fclose(fp);
    printf("load %d stopWords.\n", count);
    return count;
}

// 1-4.remove stopwords 
void removeStopwords(char words[][WORD_LONG],int *wordCount,char stopwords[][WORD_LONG],int stopCount){
    if(stopCount<=0||*wordCount<=0){
        return;//No stopwords or no words, void does not return a value
    }
    int newCount=0;
    for(int i=0;i<*wordCount;i++){//traverse all words
        int stop=0;// Flag to track if it has been found
        for(int j=0;j<stopCount;j++){
            if(strcmp(words[i],stopwords[j])==0) { //same
                stop=1;//already found
                break;// find it & exit
            }
        }if(stop==0){// if is not stopword
            if(newCount!=i){//If previously stop==1, it should be deleted and shifted forward
                strcpy(words[newCount],words[i]);
            }
            newCount++;
        }
    }
    printf("Stopwords removed:%d\n",*wordCount-newCount);//substraction
    *wordCount=newCount;//update word count
}

// 2.check toxic words
int toxicWordCheck(const char words[][WORD_LONG],int wordCount){ //Use data from the previous function
    FILE *toxic=fopen("toxicWords.txt","r");
    if (toxic==NULL){   //open failed
        printf("opened failed!\n");
        return 0;   //return！
    } 
    char toxicWord[WORD_LONG];
    char toxicList[500] [WORD_LONG];
    int toxicCount=0;// for count toxic words
    int detectedToxicCount=0;
    int toxicFrequence[500]={0};    // for counting frequency of each toxic word
    //读取toxiclist
    while (fscanf(toxic,"%39s",toxicWord) == 1&& toxicCount<500) {//scanf  
        for(int k=0;toxicWord[k];k++){
            toxicWord[k]=tolower(toxicWord[k]);// become lowercase
        }
        strcpy(toxicList[toxicCount],toxicWord);//string copy
        toxicCount++;
    }
    fclose(toxic); 
    //check same 
    for(int i=0;i<wordCount;i++){
        for(int j=0;j<toxicCount;j++){//compare if equal
            if(strcmp(words[i],toxicList[j])==0){// if same
                detectedToxicCount++;
                toxicFrequence[j]++;      // frequency +1
            }
        }
    }
    printf("find %d toxic words\n",detectedToxicCount);//output
    //frequeny table
    printf("Toxic word frequency table:\n");
    for(int j=0;j<toxicCount;j++){
        if(toxicFrequence[j]>0){
            printf("%s:%d\n",toxicList[j],toxicFrequence[j]);
        }
    }
    return detectedToxicCount;//return value
}

// 3.sorting
void sortingWords(char words[][WORD_LONG],int wordCount){//bubble sorting
    char temps[WORD_LONG];              //exchange
    for(int i=1;i<wordCount;i++){       //n-1次
        for(int j=0;j<wordCount-i;j++){//Inner loop compares adjacent j and j+1, runs 0 to n-2 (n-1 times)
            if(strcmp(words[j],words[j+1])>0){//compare first character
                strcpy(temps,words[j]);//exchange
                strcpy(words[j],words[j+1]);
                strcpy(words[j+1],temps);
            }
        }
    }
    printf("words has been queued\n");
}

// 5.Top N frequent words(most difficult)
void showTopWords(char words[][WORD_LONG], int wordCount, int topN) {
    if(wordCount<=0){//if no words
        printf("no words,cannot show topN.\n");
        return;//return
    }
    char uniqueWords[UpLimit_WORDS][WORD_LONG];
    int freq[UpLimit_WORDS]={0};
    int uniqueCount=0;
    // Count the frequency of each word
    for(int i=0;i<wordCount;i++){
        int index=-1;//Assume current words[i] is not yet in uniqueWords
        for(int j=0;j<uniqueCount;j++){
            if(strcmp(words[i],uniqueWords[j])==0){
                index=j;//find it，record index
                break;//exit
            }
        }
        if(index==-1){//new word
            strcpy(uniqueWords[uniqueCount],words[i]);//Add it to uniqueWords at the position indicated by uniqueCount
            freq[uniqueCount]=1;// first appearance
            uniqueCount++;// unique word +1
        }else{
            freq[index]++;// existing word's frequency +1
        }
    }
    // sort by frequency
    for(int i=0;i<uniqueCount-1;i++){
        for(int j=i+1;j<uniqueCount;j++){
            if(freq[j]>freq[i]){// If the frequency at position j is greater than at position i, swap them
                int temp = freq[i];// exchange
                freq[i]=freq[j];
                freq[j]=temp;

                char tempW[WORD_LONG];// exchange
                strcpy(tempW, uniqueWords[i]);
                strcpy(uniqueWords[i], uniqueWords[j]);
                strcpy(uniqueWords[j], tempW);
            }
        }
    }
    int N=topN;
    if(N>uniqueCount){//If the requested top N is larger than the total number of unique words, just display all unique words
        N=uniqueCount;
    }printf("Top %d frequent words:\n",N);
    for(int i=0;i<N;i++){
        printf("%s:%d\n",uniqueWords[i],freq[i]);
    }
}

// 4-1.average word length
double averageWordLength(char words[][WORD_LONG], int wordCount){
    if (wordCount<=0){
        return 0.0;
    }
    int totalChars=0;
    for (int i=0;i<wordCount;i++) {
        totalChars+=(int)strlen(words[i]);
    }
    return (double)totalChars/wordCount;
}

// 4-2.generate report
void generateReport(int allWordCount,int toxicCount,int uniqueCount,double avgWordLen){//robustness
    FILE *report=fopen("reportTemp.txt","w");// write into mode
    if(report==NULL){
        printf("open error\n");
        return ;//void cannot return value
    }
    fprintf(report,"le vocabulaire analyse rapport\n");
    fprintf(report,"vocabulaire nombre:%d\n",allWordCount);
    fprintf(report,"toxic nombre:%d\n",toxicCount);
    fprintf(report,"unique words:%d\n",uniqueCount);    //output unique word count
    if(allWordCount==0){//divisor not zero
        fprintf(report,"toxic pourcentage:0.00%%\n");// Avoid division by zero error
        fprintf(report,"lexical diversity:0.00\n");  
        fprintf(report,"average word length:0.00\n");
    }
    else{
        fprintf(report,"toxic pourcentage:%.2f%%\n",((float)toxicCount/allWordCount)*100);//turn to percentage
        fprintf(report,"lexical diversity:%.2f\n",(double)uniqueCount / allWordCount);
        fprintf(report,"average word length:%.2f\n", avgWordLen);
    }
    fclose(report);
    //To avoid write errors: note that using w mode will erase the original file when you write to it.
    if (rename("reportTemp.txt","analyse_report.txt")!=0){ // if ==0, success
        //If the rename fails, try removing the existing report and then rename the new file.
        remove("analyse_report.txt");
        if (rename("reportTemp.txt","analyse_report.txt")!=0){
            printf("failure~~403 litte dinosaure link start!!");// rename failed
            return;
        }
    }else{
        printf("mission complete,report generated\n");// rename success
    }
}

// 6.UI menu
void monMenu(){// print menu
    printf("\nhey!Here is toxic word analyser:\n");
    printf("1.load file words\n(Please make sure that your text file is in the \"output\" folder)\n");
    printf("2.detecting toxic words\n");
    printf("3.sorting words\n");
    printf("4.generate report\n");
    printf("5.report summary\n");
    printf("6.exit programmme\n");
    printf("please select(sorosoro sentaku da):");//choice
}


//main function
int main(){
    char words[UpLimit_WORDS][WORD_LONG];// list of words
    int wordInput=0;
    int toxicWordInput=0;
    int uniqueWordInput=0;
    int choice;
    char file[40];//get file
    char stopwords[UpLimit_WORDS][WORD_LONG]; // list of stop words
    int stopCount=0;                        // number of stop word

    stopCount = loadStopwords(stopwords);
    printf("Bienvenue!C'est le programme d'analyse de vocabulaire:\n");// welcome to text analyzer programme
    // Select specific file
    while(1){
        monMenu();
        int flag=scanf("%d",&choice);//Check return value, determine if it is a number
        if(flag!=1){// if return value not a number
            while(getchar()!='\n'){}//getchar, clear buffer
            printf("please input number:\n");
            continue;//back to top
        }
        while(getchar()!='\n');//clear other things in buffer
        
        switch(choice){//The switch must be placed inside the while loop, otherwise the menu won't display
            case 1:
                printf("input file name:\n");
                scanf("%39s",file);
                wordInput=loadWords(file,words);//load words
                if (stopCount>0){
                    removeStopwords(words, &wordInput, stopwords, stopCount);
                }
                uniqueWordInput=countUniqueWords(words, wordInput);
                break;
            case 2:
                if(wordInput==0){// check if words loaded
                    printf("load words,onegaishimasu\n");
                    break;// break case
                }
                else{
                    toxicWordInput=toxicWordCheck(words,wordInput);// check toxic words
                }break;
            case 3:
                if(wordInput==0){
                    printf("load words,onegaishimasu\n");
                    break;//break case
                }else{
                sortingWords(words,wordInput);         // sort words
                }break;
            case 4:
                if(wordInput==0){
                    printf("load words,onegaishimasu\n");
                    break;// break case
                }else{
                    double avgLen = averageWordLength(words, wordInput);
                    generateReport(wordInput,toxicWordInput,uniqueWordInput,avgLen);
                }break;
            case 5:
                printf("analyse complete:\n");
                printf("total words:%d\n",wordInput);
                printf("toxic words:%d\n",toxicWordInput);
                printf("unique words:%d\n",uniqueWordInput);
                if (wordInput==0){
                    printf("toxic percentage:0.00%%\n");// Avoid division by zero error
                    printf("lexical diversity:0.00\n");
                    printf("average word length:0.00\n");
                }else{
                    printf("toxic percentage:%.2f%%\n",((float)toxicWordInput/wordInput)*100);// print percentage
                    printf("lexical diversity:%.2f\n",(double)uniqueWordInput/wordInput);
                    printf("average word length:%.2f\n", averageWordLength(words, wordInput));
                }if (wordInput>0) {
                    showTopWords(words, wordInput, 5);
                }break;
            case 6:
                printf("Au revoir~\n");
                return 0;//exit
            default:// if not 1-6
                printf("error number\n");// Since it's the last case, it will loop back to the menu
        }
    }
    return 0;
}
