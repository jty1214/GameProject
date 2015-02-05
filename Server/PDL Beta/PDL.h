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
			for(_int32 friendListi;friendListi<;friendList.size();friendListi++) {
				size += sizeof(_int32);
				size += (sizeof(char)*userName.length());
				size += sizeof(_int64);
				size += sizeof(_int32);
				size += sizeof(_int32);
			}
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&friendList.size()), sizeof(friendList.size()));
			ptr += sizeof(friendList);
			for(_int32 friendListi=0;friendListi<friendList.size();friendListi++) {
				memcpy(ptr, (void *)(&userName.length()), sizeof(_int32));
				ptr += sizeof(_int32);
				for(_int32 i=0;i<userName.length();i++) {
					memcpy(ptr, (void *)(&userName.at(i)), sizeof(char));
					ptr += sizeof(char);
				}
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
			for(_int32 firstListi;firstListi<;firstList.size();firstListi++) {
				size += sizeof(_int32);
				size += (sizeof(char)*stringFirstListVariable.length());
				size += sizeof(_int64);
				size += sizeof(_int32);
				size += sizeof(bool);
				size += sizeof(_int32);
				for(_int32 secondListi;secondListi<;secondList.size();secondListi++) {
					size += sizeof(_int32);
					size += (sizeof(char)*stringSecondListVariable.length());
					size += sizeof(_int64);
					size += sizeof(_int32);
					size += sizeof(bool);
					size += sizeof(_int32);
					for(_int32 thirdListi;thirdListi<;thirdList.size();thirdListi++) {
						size += sizeof(_int32);
						size += (sizeof(char)*stringThirdListVariable.length());
						size += sizeof(_int64);
						size += sizeof(_int32);
						size += sizeof(bool);
					}
					size += sizeof(_int32);
					size += (sizeof(char)*endofSecondVariable.length());
				}
				size += sizeof(_int32);
				for(_int32 specialListi;specialListi<;specialList.size();specialListi++) {
					size += sizeof(_int32);
					size += (sizeof(char)*stringSpecialListVariable.length());
					size += sizeof(_int64);
					size += sizeof(_int32);
					size += sizeof(bool);
				}
			}
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&firstList.size()), sizeof(firstList.size()));
			ptr += sizeof(firstList);
			for(_int32 firstListi=0;firstListi<firstList.size();firstListi++) {
				memcpy(ptr, (void *)(&stringFirstListVariable.length()), sizeof(_int32));
				ptr += sizeof(_int32);
				for(_int32 i=0;i<stringFirstListVariable.length();i++) {
					memcpy(ptr, (void *)(&stringFirstListVariable.at(i)), sizeof(char));
					ptr += sizeof(char);
				}
				memcpy(ptr, (void *)(&longFirstListVariable), sizeof(longFirstListVariable));
				ptr += sizeof(longFirstListVariable);
				memcpy(ptr, (void *)(&intFirstListVariable), sizeof(intFirstListVariable));
				ptr += sizeof(intFirstListVariable);
				memcpy(ptr, (void *)(&boolFirstListVariable), sizeof(boolFirstListVariable));
				ptr += sizeof(boolFirstListVariable);
				memcpy(ptr, (void *)(&secondList.size()), sizeof(secondList.size()));
				ptr += sizeof(secondList);
				for(_int32 secondListi=0;secondListi<secondList.size();secondListi++) {
					memcpy(ptr, (void *)(&stringSecondListVariable.length()), sizeof(_int32));
					ptr += sizeof(_int32);
					for(_int32 i=0;i<stringSecondListVariable.length();i++) {
						memcpy(ptr, (void *)(&stringSecondListVariable.at(i)), sizeof(char));
						ptr += sizeof(char);
					}
					memcpy(ptr, (void *)(&longSecondListVariable), sizeof(longSecondListVariable));
					ptr += sizeof(longSecondListVariable);
					memcpy(ptr, (void *)(&intSecondListVariable), sizeof(intSecondListVariable));
					ptr += sizeof(intSecondListVariable);
					memcpy(ptr, (void *)(&boolSecondListVariable), sizeof(boolSecondListVariable));
					ptr += sizeof(boolSecondListVariable);
					memcpy(ptr, (void *)(&thirdList.size()), sizeof(thirdList.size()));
					ptr += sizeof(thirdList);
					for(_int32 thirdListi=0;thirdListi<thirdList.size();thirdListi++) {
						memcpy(ptr, (void *)(&stringThirdListVariable.length()), sizeof(_int32));
						ptr += sizeof(_int32);
						for(_int32 i=0;i<stringThirdListVariable.length();i++) {
							memcpy(ptr, (void *)(&stringThirdListVariable.at(i)), sizeof(char));
							ptr += sizeof(char);
						}
						memcpy(ptr, (void *)(&longThirdListVariable), sizeof(longThirdListVariable));
						ptr += sizeof(longThirdListVariable);
						memcpy(ptr, (void *)(&intThirdListVariable), sizeof(intThirdListVariable));
						ptr += sizeof(intThirdListVariable);
						memcpy(ptr, (void *)(&boolThirdListVariable), sizeof(boolThirdListVariable));
						ptr += sizeof(boolThirdListVariable);
					}
					memcpy(ptr, (void *)(&endofSecondVariable.length()), sizeof(_int32));
					ptr += sizeof(_int32);
					for(_int32 i=0;i<endofSecondVariable.length();i++) {
						memcpy(ptr, (void *)(&endofSecondVariable.at(i)), sizeof(char));
						ptr += sizeof(char);
					}
				}
				memcpy(ptr, (void *)(&specialList.size()), sizeof(specialList.size()));
				ptr += sizeof(specialList);
				for(_int32 specialListi=0;specialListi<specialList.size();specialListi++) {
					memcpy(ptr, (void *)(&stringSpecialListVariable.length()), sizeof(_int32));
					ptr += sizeof(_int32);
					for(_int32 i=0;i<stringSpecialListVariable.length();i++) {
						memcpy(ptr, (void *)(&stringSpecialListVariable.at(i)), sizeof(char));
						ptr += sizeof(char);
					}
					memcpy(ptr, (void *)(&longSpecialListVariable), sizeof(longSpecialListVariable));
					ptr += sizeof(longSpecialListVariable);
					memcpy(ptr, (void *)(&intSpecialListVariable), sizeof(intSpecialListVariable));
					ptr += sizeof(intSpecialListVariable);
					memcpy(ptr, (void *)(&boolSpecialListVariable), sizeof(boolSpecialListVariable));
					ptr += sizeof(boolSpecialListVariable);
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
				str = new char[str_len+1]
				for(_int32 i=0;i<str_len;i++) {
					memcpy(str+i, (char *)byteStream + index, sizeof(char));
					index += sizeof(char);
				}
				str[str_len] = '\0';
				stringFirstListVariable = string(str);
				delete str;
				memcpy(&longFirstListVariable, (char *)byteStream + index, sizeof(_int64));
				index += sizeof(longFirstListVariable);
				memcpy(&intFirstListVariable, (char *)byteStream + index, sizeof(_int32));
				index += sizeof(intFirstListVariable);
				memcpy(&boolFirstListVariable, (char *)byteStream + index, sizeof(bool));
				index += sizeof(boolFirstListVariable);
				_int32 secondListLength;
				memcpy(&secondListLength, (char *)byteStream + index, sizeof(_int32));
				index += sizeof(secondListLength);
				for(_int32 secondListi=0;secondListi<secondListLength;secondListi++) {
					TEST_FIRST_LIST::TEST_SECOND_LIST secondListit;
					memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					str = new char[str_len+1]
					for(_int32 i=0;i<str_len;i++) {
						memcpy(str+i, (char *)byteStream + index, sizeof(char));
						index += sizeof(char);
					}
					str[str_len] = '\0';
					stringSecondListVariable = string(str);
					delete str;
					memcpy(&longSecondListVariable, (char *)byteStream + index, sizeof(_int64));
					index += sizeof(longSecondListVariable);
					memcpy(&intSecondListVariable, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(intSecondListVariable);
					memcpy(&boolSecondListVariable, (char *)byteStream + index, sizeof(bool));
					index += sizeof(boolSecondListVariable);
					_int32 thirdListLength;
					memcpy(&thirdListLength, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(thirdListLength);
					for(_int32 thirdListi=0;thirdListi<thirdListLength;thirdListi++) {
						TEST_FIRST_LIST::TEST_SECOND_LIST::TEST_THIRD_LIST thirdListit;
						memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
						index += sizeof(str_len);
						str = new char[str_len+1]
						for(_int32 i=0;i<str_len;i++) {
							memcpy(str+i, (char *)byteStream + index, sizeof(char));
							index += sizeof(char);
						}
						str[str_len] = '\0';
						stringThirdListVariable = string(str);
						delete str;
						memcpy(&longThirdListVariable, (char *)byteStream + index, sizeof(_int64));
						index += sizeof(longThirdListVariable);
						memcpy(&intThirdListVariable, (char *)byteStream + index, sizeof(_int32));
						index += sizeof(intThirdListVariable);
						memcpy(&boolThirdListVariable, (char *)byteStream + index, sizeof(bool));
						index += sizeof(boolThirdListVariable);
						secondListit.thirdList.push_back(thirdListit);
					}
					memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					str = new char[str_len+1]
					for(_int32 i=0;i<str_len;i++) {
						memcpy(str+i, (char *)byteStream + index, sizeof(char));
						index += sizeof(char);
					}
					str[str_len] = '\0';
					endofSecondVariable = string(str);
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
					str = new char[str_len+1]
					for(_int32 i=0;i<str_len;i++) {
						memcpy(str+i, (char *)byteStream + index, sizeof(char));
						index += sizeof(char);
					}
					str[str_len] = '\0';
					stringSpecialListVariable = string(str);
					delete str;
					memcpy(&longSpecialListVariable, (char *)byteStream + index, sizeof(_int64));
					index += sizeof(longSpecialListVariable);
					memcpy(&intSpecialListVariable, (char *)byteStream + index, sizeof(_int32));
					index += sizeof(intSpecialListVariable);
					memcpy(&boolSpecialListVariable, (char *)byteStream + index, sizeof(bool));
					index += sizeof(boolSpecialListVariable);
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
			memcpy(ptr, (void *)(&keyword.length()), sizeof(_int32));
			ptr += sizeof(_int32);
			for(_int32 i=0;i<keyword.length();i++) {
				memcpy(ptr, (void *)(&keyword.at(i)), sizeof(char));
				ptr += sizeof(char);
			}
		}

		void Parsing(void* byteStream) {
			_int32 index = 0, str_len;
			char *str;
			memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));
			index += sizeof(str_len);
			str = new char[str_len+1]
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
