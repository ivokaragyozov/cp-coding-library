const int32_t MAX_N = 6e5;

const int32_t CNT = 3;
const int32_t BASE[] = { 131, 137, 149 };
const int32_t MOD[] = { (int32_t )1e9 + 7, (int32_t) 1e9 + 9, (int32_t) 1e9 + 7 };

bool initBases = false;
int32_t basePowers[CNT][MAX_N + 5];

struct Hash {
	int32_t len;
	int32_t h[CNT], rev[CNT];
	
	Hash() {
		memset(h, 0, sizeof(h));
		memset(rev, 0, sizeof(rev));
		len = 0;
	}
	Hash(std::string s) {
		memset(h, 0, sizeof(h));
		memset(rev, 0, sizeof(rev));

		if(!initBases) {
			for(int32_t p = 0; p < CNT; p++) {
				for(int32_t i = 0; i < MAX_N + 5; i++) {
					if(i == 0) {
						basePowers[p][0] = 1;
					}
					else {
						basePowers[p][i] = (int64_t) basePowers[p][i - 1] * BASE[p] % MOD[p];
					}
				}
			}

			initBases = true;
		}
		
		len = s.size();
		for(int32_t p = 0; p < CNT; p++) {
			for(int32_t i = 0; i < s.size(); i++) {
				int32_t aux = s[i] - 'a' + 1;
				h[p] = ((int64_t) h[p] + (int64_t) basePowers[p][i] * aux) % MOD[p];
				rev[p] = ((int64_t) rev[p] + (int64_t) basePowers[p][s.size() - 1 - i] * aux) % MOD[p];
			}
		}
	}
	
	bool isPalindrome() {
		for(int32_t p = 0; p < CNT; p++) {
			if(h[p] != rev[p]) {
				return false;
			}
		}

		return true;
	}

	Hash operator+ (const Hash &o) {
		Hash res;
		
		res.len = len + o.len;
		for(int32_t p = 0; p < CNT; p++) {
			res.h[p] = ((int64_t) h[p] + (int64_t) basePowers[p][len] * o.h[p]) % MOD[p];
			res.rev[p] = ((int64_t) o.rev[p] + (int64_t) basePowers[p][o.len] * rev[p]) % MOD[p];
		}

		return res;
	}
};
