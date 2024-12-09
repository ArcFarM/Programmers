#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;
    //전체 벡터를 정렬
    sort(friends.begin(), friends.end());
    sort(gifts.begin(), gifts.end());

    //선물 수를 비교할 이차원 벡터 생성 : 원소 순서를 friends의 순서에 따름
    vector<vector<int>> giftCount(friends.size(), vector<int>(friends.size(), 0));
    //선물 지수를 비교할 벡터 생성 : 원소 순서를 friends의 순서에 따름
    vector<int> giftPlus(friends.size(), 0);
    //받을 선물 수를 비교할 벡터 생성 : 원소 순서는 friends 순서에 따름
    vector<int> result(friends.size(), 0);

    //giftCount의 각 열은 그 사람이 받은 선물, 각 행은 그 사람이 준 선물의 수
    for(int i = 0; i < gifts.size(); i++){
        //선물을 준 사람과 받은 사람
        string giver;
        string receiver;
        //문자열 자르기를 위한 위치용 변수
        int pos = -1;
        int curr_pos = 0;

        //find를 사용하여 공백 기준 자르기
        while((pos = gifts[i].find(' ', curr_pos)) != string::npos){
            giver = gifts[i].substr(0, pos);
            receiver = gifts[i].substr(pos+1);
            curr_pos = pos+1;
        }
        
        //giver와 receiver의 인덱스 찾기
        int giverIdx = find(friends.begin(), friends.end(), giver) - friends.begin();
        int receiverIdx = find(friends.begin(), friends.end(), receiver) - friends.begin();

        giftCount[giverIdx][receiverIdx]++;
    }
    
    //선물 지수 계산; 그 사람이 준 선물의 수 - 그 사람이 받은 선물의 수
    for(int i = 0; i < friends.size(); i++){
        int rowSum = 0;
        int colSum = 0;
        for(int j = 0; j < friends.size(); j++){
            rowSum += giftCount[i][j];
            colSum += giftCount[j][i];
        }
        giftPlus[i] = rowSum - colSum;
    }

    //두 사람을 비교해서 선물을 가장 많이 받을 사람 찾기
    for(int i = 0; i < friends.size(); i++){
        for(int j = 0; j < friends.size(); j++){
            //자기 자신과 선물을 주고받을 수는 없다
            if(i == j) continue;
            //두 사람이 주고받은 선물 수를 비교
            if(giftCount[i][j] > giftCount[j][i]) result[i]++;
            //모두 훑고 지나갈 것이기 때문에 [j][i]가 더 큰 경우는 중복 집계 방지를 위해 무시한다
            //두 사람이 주고받은 선물 수가 같거나 0인 경우 선물 지수를 비교
            //같은 경우에는 중복 집계 방지를 위해 집계가 끝났다면 -1로 값을 바꾼다
            if(giftCount[i][j] < 0) continue;
            if(giftCount[i][j] == giftCount[j][i]){
                if(giftPlus[i] > giftPlus[j]) result[i]++;
            }
        }
    }

    for(int i : result) answer = max(i, answer);
    
    return answer;
}