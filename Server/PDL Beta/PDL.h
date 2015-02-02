#incldue <iostream>
#incldue <list>
using namespace std;
#define BYTE unsigned char

namespace PDL
{
	class REQUEST_ENTER_CHANNEL_READ {
	public:
		int world;
		int channel;
	
		void Parsing(BYTE* byteStream) {
			int index = 0, str_len;
			memcpy(&world, (int *)byteStream + index, sizeof(int));
			index += sizeof(world);
			memcpy(&channel, (int *)byteStream + index, sizeof(int));
			index += sizeof(channel);
		}
	};
	class RESPONSE_ENTER_CHANNEL_WRITE {
	public:
		bool valid;
		long enterChannelTime;
	
		int GetStreamLength() {
			int size=0;
			size += sizeof(bool);
			size += sizeof(long);
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&valid), sizeof(valid));
			ptr += sizeof(valid);
			memcpy(ptr, (void *)(&enterChannelTime), sizeof(enterChannelTime));
			ptr += sizeof(enterChannelTime);
		}
	};
	class REQUEST_FRIEND_LIST_READ {
	public:
	};
	class RESPONSE_FRIEND_LIST_WRITE {
	public:
		class FRIEND_LIST {
		public:
			string userName = "";
			long userServerId;
			int userGrade;
			int userSubGrade;
		};
		list<FRIEND_LIST> friendList;
	
		int GetStreamLength() {
			int size=0;
			size += sizeof(int);
			for(int friendListi;friendListi<;friendList.size();friendListi++) {
				size += sizeof(int);
				size += sizeof(userName);
				size += sizeof(long);
				size += sizeof(int);
				size += sizeof(int);
			}
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&friendList.size()), sizeof(friendList.size()));
			ptr += sizeof(friendList);
			for(int friendListi=0;friendListi<friendList.size();friendListi++) {
				memcpy(ptr, (void *)(&sizeof(userName)), sizeof(sizeof(userName)));
				ptr += sizeof(sizeof(userName));
				memcpy(ptr, (void *)(&userName), sizeof(userName));
				ptr += sizeof(userName);
				memcpy(ptr, (void *)(&userServerId), sizeof(userServerId));
				ptr += sizeof(userServerId);
				memcpy(ptr, (void *)(&userGrade), sizeof(userGrade));
				ptr += sizeof(userGrade);
				memcpy(ptr, (void *)(&userSubGrade), sizeof(userSubGrade));
				ptr += sizeof(userSubGrade);
			}
		}
	};
	class TEST_TEMP_PACKET_BOTH {
	public:
		class TEST_FIRST_LIST {
		public:
			string stringFirstListVariable = "";
			long longFirstListVariable;
			int intFirstListVariable;
			bool boolFirstListVariable;
			class TEST_SECOND_LIST {
			public:
				string stringSecondListVariable = "";
				long longSecondListVariable;
				int intSecondListVariable;
				bool boolSecondListVariable;
				class TEST_THIRD_LIST {
				public:
					string stringThirdListVariable = "";
					long longThirdListVariable;
					int intThirdListVariable;
					bool boolThirdListVariable;
				};
				list<TEST_THIRD_LIST> thirdList;
				string endofSecondVariable = "";
			};
			list<TEST_SECOND_LIST> secondList;
			class TEST_SPECIAL_LIST {
			public:
				string stringSpecialListVariable = "";
				long longSpecialListVariable;
				int intSpecialListVariable;
				bool boolSpecialListVariable;
			};
			list<TEST_SPECIAL_LIST> specialList;
		};
		list<TEST_FIRST_LIST> firstList;
	
		int GetStreamLength() {
			int size=0;
			size += sizeof(int);
			for(int firstListi;firstListi<;firstList.size();firstListi++) {
				size += sizeof(int);
				size += sizeof(stringFirstListVariable);
				size += sizeof(long);
				size += sizeof(int);
				size += sizeof(bool);
				size += sizeof(int);
				for(int secondListi;secondListi<;secondList.size();secondListi++) {
					size += sizeof(int);
					size += sizeof(stringSecondListVariable);
					size += sizeof(long);
					size += sizeof(int);
					size += sizeof(bool);
					size += sizeof(int);
					for(int thirdListi;thirdListi<;thirdList.size();thirdListi++) {
						size += sizeof(int);
						size += sizeof(stringThirdListVariable);
						size += sizeof(long);
						size += sizeof(int);
						size += sizeof(bool);
					}
					size += sizeof(int);
					size += sizeof(endofSecondVariable);
					size += sizeof(int);
					for(int specialListi;specialListi<;specialList.size();specialListi++) {
						size += sizeof(int);
						size += sizeof(stringSpecialListVariable);
						size += sizeof(long);
						size += sizeof(int);
						size += sizeof(bool);
					}
				}
			}
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&firstList.size()), sizeof(firstList.size()));
			ptr += sizeof(firstList);
			for(int firstListi=0;firstListi<firstList.size();firstListi++) {
				memcpy(ptr, (void *)(&sizeof(stringFirstListVariable)), sizeof(sizeof(stringFirstListVariable)));
				ptr += sizeof(sizeof(stringFirstListVariable));
				memcpy(ptr, (void *)(&stringFirstListVariable), sizeof(stringFirstListVariable));
				ptr += sizeof(stringFirstListVariable);
				memcpy(ptr, (void *)(&longFirstListVariable), sizeof(longFirstListVariable));
				ptr += sizeof(longFirstListVariable);
				memcpy(ptr, (void *)(&intFirstListVariable), sizeof(intFirstListVariable));
				ptr += sizeof(intFirstListVariable);
				memcpy(ptr, (void *)(&boolFirstListVariable), sizeof(boolFirstListVariable));
				ptr += sizeof(boolFirstListVariable);
				memcpy(ptr, (void *)(&secondList.size()), sizeof(secondList.size()));
				ptr += sizeof(secondList);
				for(int secondListi=0;secondListi<secondList.size();secondListi++) {
					memcpy(ptr, (void *)(&sizeof(stringSecondListVariable)), sizeof(sizeof(stringSecondListVariable)));
					ptr += sizeof(sizeof(stringSecondListVariable));
					memcpy(ptr, (void *)(&stringSecondListVariable), sizeof(stringSecondListVariable));
					ptr += sizeof(stringSecondListVariable);
					memcpy(ptr, (void *)(&longSecondListVariable), sizeof(longSecondListVariable));
					ptr += sizeof(longSecondListVariable);
					memcpy(ptr, (void *)(&intSecondListVariable), sizeof(intSecondListVariable));
					ptr += sizeof(intSecondListVariable);
					memcpy(ptr, (void *)(&boolSecondListVariable), sizeof(boolSecondListVariable));
					ptr += sizeof(boolSecondListVariable);
					memcpy(ptr, (void *)(&thirdList.size()), sizeof(thirdList.size()));
					ptr += sizeof(thirdList);
					for(int thirdListi=0;thirdListi<thirdList.size();thirdListi++) {
						memcpy(ptr, (void *)(&sizeof(stringThirdListVariable)), sizeof(sizeof(stringThirdListVariable)));
						ptr += sizeof(sizeof(stringThirdListVariable));
						memcpy(ptr, (void *)(&stringThirdListVariable), sizeof(stringThirdListVariable));
						ptr += sizeof(stringThirdListVariable);
						memcpy(ptr, (void *)(&longThirdListVariable), sizeof(longThirdListVariable));
						ptr += sizeof(longThirdListVariable);
						memcpy(ptr, (void *)(&intThirdListVariable), sizeof(intThirdListVariable));
						ptr += sizeof(intThirdListVariable);
						memcpy(ptr, (void *)(&boolThirdListVariable), sizeof(boolThirdListVariable));
						ptr += sizeof(boolThirdListVariable);
					}
					memcpy(ptr, (void *)(&sizeof(endofSecondVariable)), sizeof(sizeof(endofSecondVariable)));
					ptr += sizeof(sizeof(endofSecondVariable));
					memcpy(ptr, (void *)(&endofSecondVariable), sizeof(endofSecondVariable));
					ptr += sizeof(endofSecondVariable);
				}
				memcpy(ptr, (void *)(&specialList.size()), sizeof(specialList.size()));
				ptr += sizeof(specialList);
				for(int specialListi=0;specialListi<specialList.size();specialListi++) {
					memcpy(ptr, (void *)(&sizeof(stringSpecialListVariable)), sizeof(sizeof(stringSpecialListVariable)));
					ptr += sizeof(sizeof(stringSpecialListVariable));
					memcpy(ptr, (void *)(&stringSpecialListVariable), sizeof(stringSpecialListVariable));
					ptr += sizeof(stringSpecialListVariable);
					memcpy(ptr, (void *)(&longSpecialListVariable), sizeof(longSpecialListVariable));
					ptr += sizeof(longSpecialListVariable);
					memcpy(ptr, (void *)(&intSpecialListVariable), sizeof(intSpecialListVariable));
					ptr += sizeof(intSpecialListVariable);
					memcpy(ptr, (void *)(&boolSpecialListVariable), sizeof(boolSpecialListVariable));
					ptr += sizeof(boolSpecialListVariable);
				}
			}
		}

		void Parsing(BYTE* byteStream) {
			int index = 0, str_len;
			int firstListLength;
			memcpy(&firstListLength, (int *)byteStream + index, sizeof(int));
			index += sizeof(firstListLength);
			for(int firstListi=0;firstListi<firstListLength;firstListi++) {
				TEST_FIRST_LIST firstListit;
				memcpy(&str_len, (int *)byteStream + index, sizeof(int));
				index += sizeof(str_len);
				memcpy(&stringFirstListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
				index += sizeof(stringFirstListVariable);
				memcpy(&longFirstListVariable, (long *)byteStream + index, sizeof(long));
				index += sizeof(longFirstListVariable);
				memcpy(&intFirstListVariable, (int *)byteStream + index, sizeof(int));
				index += sizeof(intFirstListVariable);
				memcpy(&boolFirstListVariable, (bool *)byteStream + index, sizeof(bool));
				index += sizeof(boolFirstListVariable);
				int secondListLength;
				memcpy(&secondListLength, (int *)byteStream + index, sizeof(int));
				index += sizeof(secondListLength);
				for(int secondListi=0;secondListi<secondListLength;secondListi++) {
					TEST_FIRST_LIST::TEST_SECOND_LIST secondListit;
					memcpy(&str_len, (int *)byteStream + index, sizeof(int));
					index += sizeof(str_len);
					memcpy(&stringSecondListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
					index += sizeof(stringSecondListVariable);
					memcpy(&longSecondListVariable, (long *)byteStream + index, sizeof(long));
					index += sizeof(longSecondListVariable);
					memcpy(&intSecondListVariable, (int *)byteStream + index, sizeof(int));
					index += sizeof(intSecondListVariable);
					memcpy(&boolSecondListVariable, (bool *)byteStream + index, sizeof(bool));
					index += sizeof(boolSecondListVariable);
					int thirdListLength;
					memcpy(&thirdListLength, (int *)byteStream + index, sizeof(int));
					index += sizeof(thirdListLength);
					for(int thirdListi=0;thirdListi<thirdListLength;thirdListi++) {
						TEST_FIRST_LIST::TEST_SECOND_LIST::TEST_THIRD_LIST thirdListit;
						memcpy(&str_len, (int *)byteStream + index, sizeof(int));
						index += sizeof(str_len);
						memcpy(&stringThirdListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
						index += sizeof(stringThirdListVariable);
						memcpy(&longThirdListVariable, (long *)byteStream + index, sizeof(long));
						index += sizeof(longThirdListVariable);
						memcpy(&intThirdListVariable, (int *)byteStream + index, sizeof(int));
						index += sizeof(intThirdListVariable);
						memcpy(&boolThirdListVariable, (bool *)byteStream + index, sizeof(bool));
						index += sizeof(boolThirdListVariable);
						secondListit.thirdList.push_back(thirdListit);
					}
					memcpy(&str_len, (int *)byteStream + index, sizeof(int));
					index += sizeof(str_len);
					memcpy(&endofSecondVariable, (char *)byteStream + index, (sizeof(char)*str_len));
					index += sizeof(endofSecondVariable);
					firstListit.secondList.push_back(secondListit);
				}
				int specialListLength;
				memcpy(&specialListLength, (int *)byteStream + index, sizeof(int));
				index += sizeof(specialListLength);
				for(int specialListi=0;specialListi<specialListLength;specialListi++) {
					TEST_FIRST_LIST::TEST_SPECIAL_LIST specialListit;
					memcpy(&str_len, (int *)byteStream + index, sizeof(int));
					index += sizeof(str_len);
					memcpy(&stringSpecialListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
					index += sizeof(stringSpecialListVariable);
					memcpy(&longSpecialListVariable, (long *)byteStream + index, sizeof(long));
					index += sizeof(longSpecialListVariable);
					memcpy(&intSpecialListVariable, (int *)byteStream + index, sizeof(int));
					index += sizeof(intSpecialListVariable);
					memcpy(&boolSpecialListVariable, (bool *)byteStream + index, sizeof(bool));
					index += sizeof(boolSpecialListVariable);
					firstListit.specialList.push_back(specialListit);
				}
				firstList.push_back(firstListit);
			}
		}
	};
	class TEST_TT_PACKET_BOTH {
	public:
		string keyword = "";
	
		int GetStreamLength() {
			int size=0;
			size += sizeof(int);
			size += sizeof(keyword);
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&sizeof(keyword)), sizeof(sizeof(keyword)));
			ptr += sizeof(sizeof(keyword));
			memcpy(ptr, (void *)(&keyword), sizeof(keyword));
			ptr += sizeof(keyword);
		}

		void Parsing(BYTE* byteStream) {
			int index = 0, str_len;
			memcpy(&str_len, (int *)byteStream + index, sizeof(int));
			index += sizeof(str_len);
			memcpy(&keyword, (char *)byteStream + index, (sizeof(char)*str_len));
			index += sizeof(keyword);
		}
	};
}
