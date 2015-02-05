#include <iostream>
#include <vector>
using namespace std;
namespace PDL
{
	class REQUEST_ENTER_CHANNEL_READ {
	public:
		_int32 world;
		_int32 channel;
	
		void Parsing(void* byteStream) {
			_int32 index = 0, str_len;
			char *str;
			memcpy(&world, (char *)byteStream + index, sizeof(_int32));
			index += sizeof(world);
			memcpy(&channel, (char *)byteStream + index, sizeof(_int32));
			index += sizeof(channel);
		}
	};
	class RESPONSE_ENTER_CHANNEL_WRITE {
	public:
		bool valid;
		_int64 enterChannelTime;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(bool);
			size += sizeof(_int64);
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
			string userName;
			_int64 userServerId;
			_int32 userGrade;
			_int32 userSubGrade;
		};
		vector<FRIEND_LIST> friendList;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(_int32);
			for(_int32 friendListi=0;friendListi<friendList.size();friendListi++) {
				size += sizeof(_int32);
				size += (sizeof(char)*friendList.at(friendListi).userName.length());
				size += sizeof(_int64);
				size += sizeof(_int32);
				size += sizeof(_int32);
			}
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			int friendListSize = friendList.size();
			memcpy(ptr, (void *)(&friendListSize), sizeof(friendListSize));
			ptr += sizeof(friendListSize);
			for(_int32 friendListi=0;friendListi<friendListSize;friendListi++) {
				int userNameLength = friendList.at(friendListi).userName.length();
				memcpy(ptr, (void *)(&userNameLength), sizeof(_int32));
				ptr += sizeof(_int32);
				for(_int32 i=0;i<userNameLength;i++) {
					memcpy(ptr, (void *)(&friendList.at(friendListi).userName.at(i)), sizeof(char));
					ptr += sizeof(char);
				}
				memcpy(ptr, (void *)(&friendList.at(friendListi).userServerId), sizeof(friendList.at(friendListi).userServerId));
				ptr += sizeof(friendList.at(friendListi).userServerId);
				memcpy(ptr, (void *)(&friendList.at(friendListi).userGrade), sizeof(friendList.at(friendListi).userGrade));
				ptr += sizeof(friendList.at(friendListi).userGrade);
				memcpy(ptr, (void *)(&friendList.at(friendListi).userSubGrade), sizeof(friendList.at(friendListi).userSubGrade));
				ptr += sizeof(friendList.at(friendListi).userSubGrade);
			}
		}
	};
	class TEST_TEMP_PACKET_BOTH {
	public:
		class TEST_FIRST_LIST {
		public:
			string stringFirstListVariable;
			_int64 longFirstListVariable;
			_int32 intFirstListVariable;
			bool boolFirstListVariable;
			class TEST_SECOND_LIST {
			public:
				string stringSecondListVariable;
				_int64 longSecondListVariable;
				_int32 intSecondListVariable;
				bool boolSecondListVariable;
				class TEST_THIRD_LIST {
				public:
					string stringThirdListVariable;
					_int64 longThirdListVariable;
					_int32 intThirdListVariable;
					bool boolThirdListVariable;
				};
				vector<TEST_THIRD_LIST> thirdList;
				string endofSecondVariable;
			};
			vector<TEST_SECOND_LIST> secondList;
			class TEST_SPECIAL_LIST {
			public:
				string stringSpecialListVariable;
				_int64 longSpecialListVariable;
				_int32 intSpecialListVariable;
				bool boolSpecialListVariable;
			};
			vector<TEST_SPECIAL_LIST> specialList;
		};
		vector<TEST_FIRST_LIST> firstList;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(_int32);
			for(_int32 firstListi=0;firstListi<firstList.size();firstListi++) {
				size += sizeof(_int32);
				size += (sizeof(char)*firstList.at(firstListi).stringFirstListVariable.length());
				size += sizeof(_int64);
				size += sizeof(_int32);
				size += sizeof(bool);
				size += sizeof(_int32);
				for(_int32 secondListi=0;secondListi<firstList.at(firstListi).secondList.size();secondListi++) {
					size += sizeof(_int32);
					size += (sizeof(char)*firstList.at(firstListi).secondList.at(secondListi).stringSecondListVariable.length());
					size += sizeof(_int64);
					size += sizeof(_int32);
					size += sizeof(bool);
					size += sizeof(_int32);
					for(_int32 thirdListi=0;thirdListi<firstList.at(firstListi).secondList.at(secondListi).thirdList.size();thirdListi++) {
						size += sizeof(_int32);
						size += (sizeof(char)*firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).stringThirdListVariable.length());
						size += sizeof(_int64);
						size += sizeof(_int32);
						size += sizeof(bool);
					}
					size += sizeof(_int32);
					size += (sizeof(char)*firstList.at(firstListi).secondList.at(secondListi).endofSecondVariable.length());
				}
				size += sizeof(_int32);
				for(_int32 specialListi=0;specialListi<firstList.at(firstListi).specialList.size();specialListi++) {
					size += sizeof(_int32);
					size += (sizeof(char)*firstList.at(firstListi).specialList.at(specialListi).stringSpecialListVariable.length());
					size += sizeof(_int64);
					size += sizeof(_int32);
					size += sizeof(bool);
				}
			}
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			int firstListSize = firstList.size();
			memcpy(ptr, (void *)(&firstListSize), sizeof(firstListSize));
			ptr += sizeof(firstListSize);
			for(_int32 firstListi=0;firstListi<firstListSize;firstListi++) {
				int stringFirstListVariableLength = firstList.at(firstListi).stringFirstListVariable.length();
				memcpy(ptr, (void *)(&stringFirstListVariableLength), sizeof(_int32));
				ptr += sizeof(_int32);
				for(_int32 i=0;i<stringFirstListVariableLength;i++) {
					memcpy(ptr, (void *)(&firstList.at(firstListi).stringFirstListVariable.at(i)), sizeof(char));
					ptr += sizeof(char);
				}
				memcpy(ptr, (void *)(&firstList.at(firstListi).longFirstListVariable), sizeof(firstList.at(firstListi).longFirstListVariable));
				ptr += sizeof(firstList.at(firstListi).longFirstListVariable);
				memcpy(ptr, (void *)(&firstList.at(firstListi).intFirstListVariable), sizeof(firstList.at(firstListi).intFirstListVariable));
				ptr += sizeof(firstList.at(firstListi).intFirstListVariable);
				memcpy(ptr, (void *)(&firstList.at(firstListi).boolFirstListVariable), sizeof(firstList.at(firstListi).boolFirstListVariable));
				ptr += sizeof(firstList.at(firstListi).boolFirstListVariable);
				int secondListSize = firstList.at(firstListi).secondList.size();
				memcpy(ptr, (void *)(&secondListSize), sizeof(secondListSize));
				ptr += sizeof(secondListSize);
				for(_int32 secondListi=0;secondListi<secondListSize;secondListi++) {
					int stringSecondListVariableLength = firstList.at(firstListi).secondList.at(secondListi).stringSecondListVariable.length();
					memcpy(ptr, (void *)(&stringSecondListVariableLength), sizeof(_int32));
					ptr += sizeof(_int32);
					for(_int32 i=0;i<stringSecondListVariableLength;i++) {
						memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).stringSecondListVariable.at(i)), sizeof(char));
						ptr += sizeof(char);
					}
					memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).longSecondListVariable), sizeof(firstList.at(firstListi).secondList.at(secondListi).longSecondListVariable));
					ptr += sizeof(firstList.at(firstListi).secondList.at(secondListi).longSecondListVariable);
					memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).intSecondListVariable), sizeof(firstList.at(firstListi).secondList.at(secondListi).intSecondListVariable));
					ptr += sizeof(firstList.at(firstListi).secondList.at(secondListi).intSecondListVariable);
					memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).boolSecondListVariable), sizeof(firstList.at(firstListi).secondList.at(secondListi).boolSecondListVariable));
					ptr += sizeof(firstList.at(firstListi).secondList.at(secondListi).boolSecondListVariable);
					int thirdListSize = firstList.at(firstListi).secondList.at(secondListi).thirdList.size();
					memcpy(ptr, (void *)(&thirdListSize), sizeof(thirdListSize));
					ptr += sizeof(thirdListSize);
					for(_int32 thirdListi=0;thirdListi<thirdListSize;thirdListi++) {
						int stringThirdListVariableLength = firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).stringThirdListVariable.length();
						memcpy(ptr, (void *)(&stringThirdListVariableLength), sizeof(_int32));
						ptr += sizeof(_int32);
						for(_int32 i=0;i<stringThirdListVariableLength;i++) {
							memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).stringThirdListVariable.at(i)), sizeof(char));
							ptr += sizeof(char);
						}
						memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).longThirdListVariable), sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).longThirdListVariable));
						ptr += sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).longThirdListVariable);
						memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).intThirdListVariable), sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).intThirdListVariable));
						ptr += sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).intThirdListVariable);
						memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).boolThirdListVariable), sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).boolThirdListVariable));
						ptr += sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).boolThirdListVariable);
					}
					int endofSecondVariableLength = firstList.at(firstListi).secondList.at(secondListi).endofSecondVariable.length();
					memcpy(ptr, (void *)(&endofSecondVariableLength), sizeof(_int32));
					ptr += sizeof(_int32);
					for(_int32 i=0;i<endofSecondVariableLength;i++) {
						memcpy(ptr, (void *)(&firstList.at(firstListi).secondList.at(secondListi).endofSecondVariable.at(i)), sizeof(char));
						ptr += sizeof(char);
					}
				}
				int specialListSize = firstList.at(firstListi).specialList.size();
				memcpy(ptr, (void *)(&specialListSize), sizeof(specialListSize));
				ptr += sizeof(specialListSize);
				for(_int32 specialListi=0;specialListi<specialListSize;specialListi++) {
					int stringSpecialListVariableLength = firstList.at(firstListi).specialList.at(specialListi).stringSpecialListVariable.length();
					memcpy(ptr, (void *)(&stringSpecialListVariableLength), sizeof(_int32));
					ptr += sizeof(_int32);
					for(_int32 i=0;i<stringSpecialListVariableLength;i++) {
						memcpy(ptr, (void *)(&firstList.at(firstListi).specialList.at(specialListi).stringSpecialListVariable.at(i)), sizeof(char));
						ptr += sizeof(char);
					}
					memcpy(ptr, (void *)(&firstList.at(firstListi).specialList.at(specialListi).longSpecialListVariable), sizeof(firstList.at(firstListi).specialList.at(specialListi).longSpecialListVariable));
					ptr += sizeof(firstList.at(firstListi).specialList.at(specialListi).longSpecialListVariable);
					memcpy(ptr, (void *)(&firstList.at(firstListi).specialList.at(specialListi).intSpecialListVariable), sizeof(firstList.at(firstListi).specialList.at(specialListi).intSpecialListVariable));
					ptr += sizeof(firstList.at(firstListi).specialList.at(specialListi).intSpecialListVariable);
					memcpy(ptr, (void *)(&firstList.at(firstListi).specialList.at(specialListi).boolSpecialListVariable), sizeof(firstList.at(firstListi).specialList.at(specialListi).boolSpecialListVariable));
					ptr += sizeof(firstList.at(firstListi).specialList.at(specialListi).boolSpecialListVariable);
				}
			}
		}

		void Parsing(void* byteStream) {
			_int32 index = 0, str_len;
			char *str;
			_int32 firstListLength;
			memcpy(&firstListLength, (char *)byteStream + index, sizeof(_int32));
			index += sizeof(firstListLength);
			for(_int32 firstListi=0;firstListi<firstListLength;firstListi++) {
				TEST_FIRST_LIST firstListit;
				memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
				index += sizeof(str_len);
				str = new char[str_len+1];
				for(_int32 i=0;i<str_len;i++) {
					memcpy(str+i, (char *)byteStream + index, sizeof(char));
					index += sizeof(char);
				}
				str[str_len] = '\0';
				firstList.at(firstListi).stringFirstListVariable = string(str);
				delete str;
				memcpy(&firstList.at(firstListi).longFirstListVariable, (char *)byteStream + index, sizeof(_int64));
				index += sizeof(firstList.at(firstListi).longFirstListVariable);
				memcpy(&firstList.at(firstListi).intFirstListVariable, (char *)byteStream + index, sizeof(_int32));
				index += sizeof(firstList.at(firstListi).intFirstListVariable);
				memcpy(&firstList.at(firstListi).boolFirstListVariable, (char *)byteStream + index, sizeof(bool));
				index += sizeof(firstList.at(firstListi).boolFirstListVariable);
				_int32 secondListLength;
				memcpy(&secondListLength, (char *)byteStream + index, sizeof(_int32));
				index += sizeof(secondListLength);
				for(_int32 secondListi=0;secondListi<secondListLength;secondListi++) {
					TEST_FIRST_LIST::TEST_SECOND_LIST secondListit;
					memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					str = new char[str_len+1];
					for(_int32 i=0;i<str_len;i++) {
						memcpy(str+i, (char *)byteStream + index, sizeof(char));
						index += sizeof(char);
					}
					str[str_len] = '\0';
					firstList.at(firstListi).secondList.at(secondListi).stringSecondListVariable = string(str);
					delete str;
					memcpy(&firstList.at(firstListi).secondList.at(secondListi).longSecondListVariable, (char *)byteStream + index, sizeof(_int64));
					index += sizeof(firstList.at(firstListi).secondList.at(secondListi).longSecondListVariable);
					memcpy(&firstList.at(firstListi).secondList.at(secondListi).intSecondListVariable, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(firstList.at(firstListi).secondList.at(secondListi).intSecondListVariable);
					memcpy(&firstList.at(firstListi).secondList.at(secondListi).boolSecondListVariable, (char *)byteStream + index, sizeof(bool));
					index += sizeof(firstList.at(firstListi).secondList.at(secondListi).boolSecondListVariable);
					_int32 thirdListLength;
					memcpy(&thirdListLength, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(thirdListLength);
					for(_int32 thirdListi=0;thirdListi<thirdListLength;thirdListi++) {
						TEST_FIRST_LIST::TEST_SECOND_LIST::TEST_THIRD_LIST thirdListit;
						memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
						index += sizeof(str_len);
						str = new char[str_len+1];
						for(_int32 i=0;i<str_len;i++) {
							memcpy(str+i, (char *)byteStream + index, sizeof(char));
							index += sizeof(char);
						}
						str[str_len] = '\0';
						firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).stringThirdListVariable = string(str);
						delete str;
						memcpy(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).longThirdListVariable, (char *)byteStream + index, sizeof(_int64));
						index += sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).longThirdListVariable);
						memcpy(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).intThirdListVariable, (char *)byteStream + index, sizeof(_int32));
						index += sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).intThirdListVariable);
						memcpy(&firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).boolThirdListVariable, (char *)byteStream + index, sizeof(bool));
						index += sizeof(firstList.at(firstListi).secondList.at(secondListi).thirdList.at(thirdListi).boolThirdListVariable);
						secondListit.thirdList.push_back(thirdListit);
					}
					memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					str = new char[str_len+1];
					for(_int32 i=0;i<str_len;i++) {
						memcpy(str+i, (char *)byteStream + index, sizeof(char));
						index += sizeof(char);
					}
					str[str_len] = '\0';
					firstList.at(firstListi).secondList.at(secondListi).endofSecondVariable = string(str);
					delete str;
					firstListit.secondList.push_back(secondListit);
				}
				_int32 specialListLength;
				memcpy(&specialListLength, (char *)byteStream + index, sizeof(_int32));
				index += sizeof(specialListLength);
				for(_int32 specialListi=0;specialListi<specialListLength;specialListi++) {
					TEST_FIRST_LIST::TEST_SPECIAL_LIST specialListit;
					memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					str = new char[str_len+1];
					for(_int32 i=0;i<str_len;i++) {
						memcpy(str+i, (char *)byteStream + index, sizeof(char));
						index += sizeof(char);
					}
					str[str_len] = '\0';
					firstList.at(firstListi).specialList.at(specialListi).stringSpecialListVariable = string(str);
					delete str;
					memcpy(&firstList.at(firstListi).specialList.at(specialListi).longSpecialListVariable, (char *)byteStream + index, sizeof(_int64));
					index += sizeof(firstList.at(firstListi).specialList.at(specialListi).longSpecialListVariable);
					memcpy(&firstList.at(firstListi).specialList.at(specialListi).intSpecialListVariable, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(firstList.at(firstListi).specialList.at(specialListi).intSpecialListVariable);
					memcpy(&firstList.at(firstListi).specialList.at(specialListi).boolSpecialListVariable, (char *)byteStream + index, sizeof(bool));
					index += sizeof(firstList.at(firstListi).specialList.at(specialListi).boolSpecialListVariable);
					firstListit.specialList.push_back(specialListit);
				}
				firstList.push_back(firstListit);
			}
		}
	};
	class TEST_TT_PACKET_BOTH {
	public:
		string keyword;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(_int32);
			size += (sizeof(char)*keyword.length());
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			int keywordLength = keyword.length();
			memcpy(ptr, (void *)(&keywordLength), sizeof(_int32));
			ptr += sizeof(_int32);
			for(_int32 i=0;i<keywordLength;i++) {
				memcpy(ptr, (void *)(&keyword.at(i)), sizeof(char));
				ptr += sizeof(char);
			}
		}

		void Parsing(void* byteStream) {
			_int32 index = 0, str_len;
			char *str;
			memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
			index += sizeof(str_len);
			str = new char[str_len+1];
			for(_int32 i=0;i<str_len;i++) {
				memcpy(str+i, (char *)byteStream + index, sizeof(char));
				index += sizeof(char);
			}
			str[str_len] = '\0';
			keyword = string(str);
			delete str;
		}
	};
}
