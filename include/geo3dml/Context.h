#pragma once

#include <string>
#include <mutex>

namespace geo3dml {

	class Object;
	class ObjectFactory;

	/// Data context information about the Geo3DML object.
	/// These could be information related to the data source, such as XML file, remote G3DStore service etc..
	/// With the context, application could load the actual data on demand, or load data progressively.
	/// A Context object is thread safe.
	class Context {
	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		Context(ObjectFactory* g3dFactory);
		virtual ~Context();

		/// Get the bound Geo3DML object.
		/// @return The bound object.
		Object* GetGeo3DMLObject();

		/// @name Load data on demand or progressively.
		//@{
		/// Load more data from data source.
		/// This method should be overridden to load more data on demand or progressively.
		virtual void LoadMoreData();
		/// Set whether all data has been loaded.
		/// @param isDone Pass in true if all data has been loaded, or pass in false. Default is done.
		void SetDone(bool isDone);
		/// Check whether all data has been loaded.
		/// @return Return true if all data has been loaded, or return false.
		bool IsDone();
		//@}

		/// @name Status of error happening.
		//@{
		bool IsOK();
		std::string Error();
		//@}

	protected:
		friend class Object;
		/// Bind a Geo3DML object to this context.
		/// @param g3dObject The Geo3DML object to be bound with this context object, and it will not be deleted in the deconstructor of this context object.
		void BindGeo3DMLObject(Object* g3dObject);

	protected:
		/// Get the associated ObjectFactory object.
		/// @return The associated ObjectFacotry object whose lifetime is under the Context's management.
		ObjectFactory* GetObjectFactory();
		void SetStatus(bool isOK, const std::string& message = "");

		typedef std::lock_guard<std::recursive_mutex> g3dcpp_context_lock_guard;
		std::recursive_mutex mtx_;

	private:
		Object* g3dObject_;
		ObjectFactory* g3dFactory_;
		bool isDone_;
		bool isOK_;
		std::string errorMessage_;
	};
}
