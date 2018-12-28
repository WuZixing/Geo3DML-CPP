#pragma once

#include <mutex>
#include "Context.h"

namespace geo3dml {
	/// All Geo3DML objects must be thread safe.
	class Object {
	public:
		static std::string NewID();

	public:
		Object();
		virtual ~Object();

		std::string GetID();
		void SetID(const std::string& id);

		/// @name Optional Context object.
		//@{
		/// Set the associated Context object, and it will be deleted when this Geo3DML object deconstructed.
		void SetContext(Context* ctx);
		Context* GetContext();
		//@}

	protected:
		typedef std::lock_guard<std::recursive_mutex> g3d_lock_guard;
		/// The mutex object to make thread safe.
		std::recursive_mutex mtx_;

	private:
		std::string id_;
		Context* context_;
	};
}
