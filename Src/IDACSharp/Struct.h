
#pragma once

using namespace System;
using namespace System::Collections::Generic;

#include <struct.hpp>

#include "IdaHelper.h"
#include "Bytes.h"

namespace IDACSharp {

	// �ṹ���Ա
	public ref class Member {
	private:
		struc_t* sptr;
		member_t* ptr;

	internal:
		Member (struc_t* sentity, member_t* entity){
			ID = entity->id;
			Start = entity->soff;
			End = entity->eoff;
			Flag = entity->flag;
			Props = entity->props;

			sptr = sentity;
			ptr = entity;
		}

		// ���������ҽṹ�������
		static String^ GetMemberName(tid_t id) {
			char buf[256];
			get_member_name(id, buf, sizeof(buf) - 1);
			String^ str = gcnew String(buf);
			//delete[] buf;
			return str;
		}

		// ���������ҽṹ�����ȫ����
		static String^ GetMemberFullName(tid_t id) {
			char buf[256];
			get_member_fullname(id, buf, sizeof(buf) - 1);
			String^ str = gcnew String(buf);
			//delete[] buf;
			return str;
		}

		// ���������ҽṹ���ע��
		static String^ GetMemberComment(tid_t id, bool repeatable) {
			char buf[256];
			get_member_cmt(id, repeatable, buf, sizeof(buf) - 1);
			String^ str = gcnew String(buf);
			//delete[] buf;
			return str;
		}

	public:
		tid_t ID;
		ea_t Start;
		ea_t End;
		flags_t Flag;
		uint32 Props;

		//***************************��������******************************************

		// ��С
		property asize_t Size { 
			asize_t get() {
				return get_member_size(ptr); 
			}
		}
		// λ��
		property ea_t Offset { 
			ea_t get() {
				return ptr->get_soff();
			}
		}
		// ����
		property String^ Name {
			String^ get() {
				return GetMemberName(ID);
			}
			void set(String^ value) {
				set_member_name(sptr, Offset, IdaHelper::CastStringToChar(value));
			}
		}
		// ��ȫ����
		property String^ FullName {
			String^ get() {
				return GetMemberFullName(ID);
			}
		}
		// ע��
		property String^ Comment { 
			String^ get() {
				return GetMemberComment(ID, false);
			}
			void set(String^ value) {
				set_member_cmt(ptr, IdaHelper::CastStringToChar(value), false);
			}
		}

		//***************************��չ******************************************

		//// ��һ��
		//property Member^ Previous { 
		//	Member^ get() {
		//		tid_t id = get_prev_struc_idx(ID);
		//		return FindStructByID(id);
		//	}
		//}
		//// ��һ��
		//property Member^ Next { 
		//	Member^ get() {
		//		tid_t id = get_next_struc_idx(ID);
		//		return FindStructByID(id);
		//	}
		//}

		//***************************����******************************************

		// תΪ�ṹ�塣������Ϊû�취����Struct�࣬�����ֽڷ���һ��ID���Լ�����Struct
		tid_t AsStructID() {
			struc_t* entity = get_sptr(ptr);
			if (entity == NULL) return 0;

			return entity->id;
		}
	};

	// �ṹ��
	public ref class Struct
	{
	private:
		tid_t _ID;
		struc_t* ptr;

		Struct (struc_t* entity){
			ID = entity->id;
			Props = entity->props;

			if (entity->memqty > 0) {
				Members = gcnew List<Member^>();
				for(size_t i=0; i<entity->memqty; i++) {
					Member^ item = gcnew Member(entity, entity->members + i);
					Members->Add(item);
				}
			}

			ptr = entity;
		}

		// ���������ҽṹ�������
		static String^ GetStructName(tid_t id) {
			char buf[256];
			get_struc_name(id, buf, sizeof(buf) - 1);
			String^ str = gcnew String(buf);
			//delete[] buf;
			return str;
		}

		// ���������ҽṹ���ע��
		static String^ GetStructComment(tid_t id, bool repeatable) {
			char buf[256];
			get_struc_cmt(id, repeatable, buf, sizeof(buf) - 1);
			String^ str = gcnew String(buf);
			//delete[] buf;
			return str;
		}

		// ׼��������Ϣ
		static const typeinfo_t* PrepareStrucMemberTypeinfo(flags_t flag, ea_t tid, ea_t target, adiff_t tdelta, uchar reftype) {
			typeinfo_t* ti = new typeinfo_t();
			//#define FF_DATA 0x00000400L             // Data ?
			flag |= 0x00000400L;

			if (isOff0(flag)){
				refinfo_t* ri = new refinfo_t();
				ri->base = tid;

				if (target > Bytes::BadAddress){
					ri->target = target;
					ri->tdelta = 0;
					ri->flags = reftype;
				}else{
					ri->target = Bytes::BadAddress;
					ri->tdelta = 0;

					if (isWord(flag))
						ri->flags = REF_OFF16;
					else if (isByte(flag))
						ri->flags = REF_OFF8;
					else if (isQwrd(flag))
						ri->flags = REF_OFF64;
					else
						ri->flags = REF_OFF32;
				}

				ti->ri = *ri;
			} else if (isEnum0(flag)){
				enum_const_t* ec = new enum_const_t();
				ec->tid = tid;
				ec->serial = 0;
				ti->ec = *ec;
			} else if (isStroff0(flag)){
				ti->path.len = 1;
				ti->path.ids[0] = tid;
			} else {
				ti->tid = tid;
			}

			return ti;
		}

	public:
		List<Member^>^ Members;
		uint32 Props;

		//***************************��������******************************************

		// ����
		property tid_t ID { 
			tid_t get() {
				return _ID; 
			}
			void set(tid_t value) {
				if (_ID != value) {
					if (_ID != 0) {
						set_struc_idx(ptr, value);
					}
					_ID = value;
				}
			}
		}
		// ��С
		property asize_t Size { 
			asize_t get() {
				return get_struc_size(ID); 
			}
		}
		// ����
		property String^ Name {
			String^ get() {
				return GetStructName(ID);
			}
			void set(String^ value) {
				set_struc_name(ID, IdaHelper::CastStringToChar(value));
			}
		}
		// ע��
		property String^ Comment { 
			String^ get() {
				return GetStructComment(ID, false);
			}
			void set(String^ value) {
				set_struc_cmt(ID, IdaHelper::CastStringToChar(value), false);
			}
		}

		//***************************��չ******************************************

		// ��һ��
		property Struct^ Previous { 
			Struct^ get() {
				tid_t id = get_prev_struc_idx(ID);
				return FindStructByID(id);
			}
		}
		// ��һ��
		property Struct^ Next { 
			Struct^ get() {
				tid_t id = get_next_struc_idx(ID);
				return FindStructByID(id);
			}
		}

		//***************************����******************************************

		// ��ӳ�Ա��ʵ�ʱȽϸ��ӣ�����������õ�
		Member^ Add(String^ name, ea_t offset, flags_t flag, const typeinfo_t *mt, asize_t nbytes) {
			if(add_struc_member(ptr, IdaHelper::CastStringToChar(name), offset, flag, mt, nbytes) != 0) return nullptr;
			return GetMember(offset);
		}

		// ��ӳ�Ա
		Member^ Add(String^ name, ea_t offset, flags_t flag, ea_t tid, asize_t nbytes, ea_t target, adiff_t tdelta, uchar reftype) {
			const typeinfo_t* ti = PrepareStrucMemberTypeinfo(flag, tid, target, tdelta, reftype);
			if(add_struc_member(ptr, IdaHelper::CastStringToChar(name), offset, flag, ti, nbytes) != 0) return nullptr;
			return GetMember(offset);
		}

		// ��ӳ�Ա
		Member^ Add(String^ name, ea_t offset, flags_t flag, ea_t tid, asize_t nbytes) {
			return Add(name, offset, flag, tid, nbytes, Bytes::BadAddress, 0, 2);
		}

		// ��ӳ�Ա
		Member^ Add(String^ name, ea_t offset, DataType dt, ea_t tid, asize_t nbytes) {
			return Add(name, offset, (flags_t)dt, tid, nbytes);
		}

		// ��ӳ�Ա
		Member^ Add(String^ name, DataType dt, asize_t nbytes) {
			return Add(name, Bytes::BadAddress, (flags_t)dt, -1, nbytes);
		}

		// ɾ����Ա
		bool Delete(ea_t offset) {
			return del_struc_member(ptr, offset);
		}

		// ɾ����Ա
		int Delete(ea_t off1, ea_t off2) {
			return del_struc_members(ptr, off1, off2);
		}

		// ȡ�ýṹ���Ա
		Member^ GetMember(asize_t offset) {
			member_t* entity = get_member(ptr, offset);
			if (entity == NULL) return nullptr;

			return gcnew Member(ptr, entity);
		}

		// ȡ�ýṹ���Ա
		Member^ GetMemberByName(String^ name) {
			member_t* entity = get_member_by_name(ptr, IdaHelper::CastStringToChar(name));
			if (entity == NULL) return nullptr;

			return gcnew Member(ptr, entity);
		}

		// ���ó�Ա����
		bool SetMemberName(ea_t offset, String^ name) {
			return set_member_name(ptr, offset, IdaHelper::CastStringToChar(name));
		}

		//***************************��̬��Ա******************************************

		// ���������ҽṹ��
		static Struct^ FindStructByID(tid_t id) { 
			struc_t* entity = get_struc(id);
			if (entity == NULL) return nullptr;

			return gcnew Struct(entity);
		}

		// ���������ҽṹ��
		static Struct^ FindStructByName(String^ name) { 
			tid_t id = GetStructID(name);
			if (id == Bytes::BadAddress) return nullptr;

			return FindStructByID(id);
		}

		// �����ṹ��
		static Struct^ Create(String^ name, uval_t index, bool isUnion) {
			// ����
			tid_t id = add_struc(index, IdaHelper::CastStringToChar(name), isUnion);

			struc_t* entity = get_struc(id);
			if (entity == NULL) return nullptr;

			return gcnew Struct(entity);
		}

		//***************************��̬��Ա******************************************

		// �ṹ������
		static property size_t TotalCount { size_t get() { return get_struc_qty(); }}
		// ��һ��
		static property Struct^ First { 
			Struct^ get() {
				tid_t id = get_first_struc_idx();
				return FindStructByID(id);
			}
		}
		// ���һ��
		static property Struct^ Last { 
			Struct^ get() {
				tid_t id = get_last_struc_idx();
				return FindStructByID(id);
			}
		}

		// �ṹ������
		//static uval_t GetFirstStructIndex() { return get_first_struc_idx(); }
		//static uval_t GetLastStructIndex() { return get_last_struc_idx(); }
		//static uval_t GetPrevStructIndex(uval_t idx) { return get_prev_struc_idx(idx); }
		//static uval_t GetNextStructIndex(uval_t idx) { return get_next_struc_idx(idx); }
		static uval_t GetStructIndex(tid_t id) { return get_struc_idx(id); }
		static tid_t GetStructByIndex(uval_t index) { return get_struc_by_idx(index); }

		// ���������ҽṹ�������
		static tid_t GetStructID(String^ name) { return get_struc_id(IdaHelper::CastStringToChar(name)); }
	};
}