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
			memcpy(&world, (_int32 *)byteStream + index, sizeof(_int32));
			index += sizeof(world);
			memcpy(&channel, (_int32 *)byteStream + index, sizeof(_int32));
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
		list<FRIEND_LIST> friendList;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(_int32);
			for(_int32 friendListi;friendListi<;friendList.size();friendListi++) {
				size += sizeof(_int32);
				size += sizeof(userName);
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
				memcpy(ptr, (void *)(&sizeof(userName)), sizeof(_int32));
				ptr += sizeof(_int32);
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
				list<TEST_THIRD_LIST> thirdList;
				string endofSecondVariable;
			};
			list<TEST_SECOND_LIST> secondList;
			class TEST_SPECIAL_LIST {
			public:
				string stringSpecialListVariable;
				_int64 longSpecialListVariable;
				_int32 intSpecialListVariable;
				bool boolSpecialListVariable;
			};
			list<TEST_SPECIAL_LIST> specialList;
		};
		list<TEST_FIRST_LIST> firstList;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(_int32);
			for(_int32 firstListi;firstListi<;firstList.size();firstListi++) {
				size += sizeof(_int32);
				size += sizeof(stringFirstListVariable);
				size += sizeof(_int64);
				size += sizeof(_int32);
				size += sizeof(bool);
				size += sizeof(_int32);
				for(_int32 secondListi;secondListi<;secondList.size();secondListi++) {
					size += sizeof(_int32);
					size += sizeof(stringSecondListVariable);
					size += sizeof(_int64);
					size += sizeof(_int32);
					size += sizeof(bool);
					size += sizeof(_int32);
					for(_int32 thirdListi;thirdListi<;thirdList.size();thirdListi++) {
						size += sizeof(_int32);
						size += sizeof(stringThirdListVariable);
						size += sizeof(_int64);
						size += sizeof(_int32);
						size += sizeof(bool);
					}
					size += sizeof(_int32);
					size += sizeof(endofSecondVariable);
					size += sizeof(_int32);
					for(_int32 specialListi;specialListi<;specialList.size();specialListi++) {
						size += sizeof(_int32);
						size += sizeof(stringSpecialListVariable);
						size += sizeof(_int64);
						size += sizeof(_int32);
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
			for(_int32 firstListi=0;firstListi<firstList.size();firstListi++) {
				memcpy(ptr, (void *)(&sizeof(stringFirstListVariable)), sizeof(_int32));
				ptr += sizeof(_int32);
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
				for(_int32 secondListi=0;secondListi<secondList.size();secondListi++) {
					memcpy(ptr, (void *)(&sizeof(stringSecondListVariable)), sizeof(_int32));
					ptr += sizeof(_int32);
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
					for(_int32 thirdListi=0;thirdListi<thirdList.size();thirdListi++) {
						memcpy(ptr, (void *)(&sizeof(stringThirdListVariable)), sizeof(_int32));
						ptr += sizeof(_int32);
						memcpy(ptr, (void *)(&stringThirdListVariable), sizeof(stringThirdListVariable));
						ptr += sizeof(stringThirdListVariable);
						memcpy(ptr, (void *)(&longThirdListVariable), sizeof(longThirdListVariable));
						ptr += sizeof(longThirdListVariable);
						memcpy(ptr, (void *)(&intThirdListVariable), sizeof(intThirdListVariable));
						ptr += sizeof(intThirdListVariable);
						memcpy(ptr, (void *)(&boolThirdListVariable), sizeof(boolThirdListVariable));
						ptr += sizeof(boolThirdListVariable);
					}
					memcpy(ptr, (void *)(&sizeof(endofSecondVariable)), sizeof(_int32));
					ptr += sizeof(_int32);
					memcpy(ptr, (void *)(&endofSecondVariable), sizeof(endofSecondVariable));
					ptr += sizeof(endofSecondVariable);
				}
				memcpy(ptr, (void *)(&specialList.size()), sizeof(specialList.size()));
				ptr += sizeof(specialList);
				for(_int32 specialListi=0;specialListi<specialList.size();specialListi++) {
					memcpy(ptr, (void *)(&sizeof(stringSpecialListVariable)), sizeof(_int32));
					ptr += sizeof(_int32);
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

		void Parsing(void* byteStream) {
			_int32 index = 0, str_len;
			_int32 firstListLength;
			memcpy(&firstListLength, (_int32 *)byteStream + index, sizeof(_int32));
			index += sizeof(firstListLength);
			for(_int32 firstListi=0;firstListi<firstListLength;firstListi++) {
				TEST_FIRST_LIST firstListit;
				memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));
				index += sizeof(str_len);
				memcpy(&stringFirstListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
				index += sizeof(stringFirstListVariable);
				memcpy(&longFirstListVariable, (_int64 *)byteStream + index, sizeof(_int64));
				index += sizeof(longFirstListVariable);
				memcpy(&intFirstListVariable, (_int32 *)byteStream + index, sizeof(_int32));
				index += sizeof(intFirstListVariable);
				memcpy(&boolFirstListVariable, (bool *)byteStream + index, sizeof(bool));
				index += sizeof(boolFirstListVariable);
				_int32 secondListLength;
				memcpy(&secondListLength, (_int32 *)byteStream + index, sizeof(_int32));
				index += sizeof(secondListLength);
				for(_int32 secondListi=0;secondListi<secondListLength;secondListi++) {
					TEST_FIRST_LIST::TEST_SECOND_LIST secondListit;
					memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					memcpy(&stringSecondListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
					index += sizeof(stringSecondListVariable);
					memcpy(&longSecondListVariable, (_int64 *)byteStream + index, sizeof(_int64));
					index += sizeof(longSecondListVariable);
					memcpy(&intSecondListVariable, (_int32 *)byteStream + index, sizeof(_int32));
					index += sizeof(intSecondListVariable);
					memcpy(&boolSecondListVariable, (bool *)byteStream + index, sizeof(bool));
					index += sizeof(boolSecondListVariable);
					_int32 thirdListLength;
					memcpy(&thirdListLength, (_int32 *)byteStream + index, sizeof(_int32));
					index += sizeof(thirdListLength);
					for(_int32 thirdListi=0;thirdListi<thirdListLength;thirdListi++) {
						TEST_FIRST_LIST::TEST_SECOND_LIST::TEST_THIRD_LIST thirdListit;
						memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));
						index += sizeof(str_len);
						memcpy(&stringThirdListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
						index += sizeof(stringThirdListVariable);
						memcpy(&longThirdListVariable, (_int64 *)byteStream + index, sizeof(_int64));
						index += sizeof(longThirdListVariable);
						memcpy(&intThirdListVariable, (_int32 *)byteStream + index, sizeof(_int32));
						index += sizeof(intThirdListVariable);
						memcpy(&boolThirdListVariable, (bool *)byteStream + index, sizeof(bool));
						index += sizeof(boolThirdListVariable);
						secondListit.thirdList.push_back(thirdListit);
					}
					memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					memcpy(&endofSecondVariable, (char *)byteStream + index, (sizeof(char)*str_len));
					index += sizeof(endofSecondVariable);
					firstListit.secondList.push_back(secondListit);
				}
				_int32 specialListLength;
				memcpy(&specialListLength, (_int32 *)byteStream + index, sizeof(_int32));
				index += sizeof(specialListLength);
				for(_int32 specialListi=0;specialListi<specialListLength;specialListi++) {
					TEST_FIRST_LIST::TEST_SPECIAL_LIST specialListit;
					memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));
					index += sizeof(str_len);
					memcpy(&stringSpecialListVariable, (char *)byteStream + index, (sizeof(char)*str_len));
					index += sizeof(stringSpecialListVariable);
					memcpy(&longSpecialListVariable, (_int64 *)byteStream + index, sizeof(_int64));
					index += sizeof(longSpecialListVariable);
					memcpy(&intSpecialListVariable, (_int32 *)byteStream + index, sizeof(_int32));
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
		string keyword;
	
		_int32 GetStreamLength() {
			_int32 size=0;
			size += sizeof(_int32);
			size += sizeof(keyword);
			return size;
		}

		void Serialize(void* byteStream) {
			char* ptr = (char*)byteStream;
			memcpy(ptr, (void *)(&sizeof(keyword)), sizeof(_int32));
			ptr += sizeof(_int32);
			memcpy(ptr, (void *)(&keyword), sizeof(keyword));
			ptr += sizeof(keyword);
		}

		void Parsing(void* byteStream) {
			_int32 index = 0, str_len;
			memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));
			index += sizeof(str_len);
			memcpy(&keyword, (char *)byteStream + index, (sizeof(char)*str_len));
			index += sizeof(keyword);
		}
	};
}
