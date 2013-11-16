// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef ACCOUNT_ODB_HXX
#define ACCOUNT_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20300UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include <opencash/model/Account.h>

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // Account
  //
  template <>
  struct class_traits< ::opencash::model::Account >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::opencash::model::Account >
  {
    public:
    typedef ::opencash::model::Account object_type;
    typedef ::opencash::model::Account* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef ::std::string id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_op_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/sqlite-types.hxx>
#include <odb/sqlite/query.hxx>

namespace odb
{
  // Account
  //
  template <typename A>
  struct pointer_query_columns< ::opencash::model::Account, id_sqlite, A >
  {
    // uuid
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    uuid_type_;

    static const uuid_type_ uuid;

    // name
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    name_type_;

    static const name_type_ name;

    // description
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    description_type_;

    static const description_type_ description;

    // type
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::opencash::model::AccountType,
        sqlite::id_integer >::query_type,
      sqlite::id_integer >
    type_type_;

    static const type_type_ type;

    // parent
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    parent_type_;

    static const parent_type_ parent;
  };

  template <typename A>
  const typename pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::uuid_type_
  pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::
  uuid (A::table_name, "\"uuid\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::name_type_
  pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::
  name (A::table_name, "\"name\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::description_type_
  pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::
  description (A::table_name, "\"description\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::type_type_
  pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::
  type (A::table_name, "\"type\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::parent_type_
  pointer_query_columns< ::opencash::model::Account, id_sqlite, A >::
  parent (A::table_name, "\"parent\"", 0);

  template <>
  class access::object_traits_impl< ::opencash::model::Account, id_sqlite >:
    public access::object_traits< ::opencash::model::Account >
  {
    public:
    struct id_image_type
    {
      details::buffer id_value;
      std::size_t id_size;
      bool id_null;

      std::size_t version;
    };

    struct image_type
    {
      // _uuid
      //
      details::buffer _uuid_value;
      std::size_t _uuid_size;
      bool _uuid_null;

      // _name
      //
      details::buffer _name_value;
      std::size_t _name_size;
      bool _name_null;

      // _description
      //
      details::buffer _description_value;
      std::size_t _description_size;
      bool _description_null;

      // _type
      //
      long long _type_value;
      bool _type_null;

      // _parent
      //
      details::buffer _parent_value;
      std::size_t _parent_size;
      bool _parent_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    struct parent_tag;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (sqlite::bind*,
          image_type&,
          sqlite::statement_kind);

    static void
    bind (sqlite::bind*, id_image_type&);

    static bool
    init (image_type&,
          const object_type&,
          sqlite::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef sqlite::object_statements<object_type> statements_type;

    typedef sqlite::query_base query_base_type;

    static const std::size_t column_count = 5UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  template <>
  class access::object_traits_impl< ::opencash::model::Account, id_common >:
    public access::object_traits_impl< ::opencash::model::Account, id_sqlite >
  {
  };

  // Account
  //
  template <>
  struct alias_traits<
    ::opencash::model::Account,
    id_sqlite,
    access::object_traits_impl< ::opencash::model::Account, id_sqlite >::parent_tag>
  {
    static const char table_name[];
  };

  template <>
  struct query_columns_base< ::opencash::model::Account, id_sqlite >
  {
    // parent
    //
    typedef
    odb::alias_traits<
      ::opencash::model::Account,
      id_sqlite,
      access::object_traits_impl< ::opencash::model::Account, id_sqlite >::parent_tag>
    parent_alias_;
  };

  template <typename A>
  struct query_columns< ::opencash::model::Account, id_sqlite, A >:
    query_columns_base< ::opencash::model::Account, id_sqlite >
  {
    // uuid
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    uuid_type_;

    static const uuid_type_ uuid;

    // name
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    name_type_;

    static const name_type_ name;

    // description
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    description_type_;

    static const description_type_ description;

    // type
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::opencash::model::AccountType,
        sqlite::id_integer >::query_type,
      sqlite::id_integer >
    type_type_;

    static const type_type_ type;

    // parent
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    parent_column_type_;

    typedef
    odb::query_pointer<
      odb::pointer_query_columns<
        ::opencash::model::Account,
        id_sqlite,
        parent_alias_ > >
    parent_pointer_type_;

    struct parent_type_: parent_pointer_type_, parent_column_type_
    {
      parent_type_ (const char* t, const char* c, const char* conv)
        : parent_column_type_ (t, c, conv)
      {
      }
    };

    static const parent_type_ parent;
  };

  template <typename A>
  const typename query_columns< ::opencash::model::Account, id_sqlite, A >::uuid_type_
  query_columns< ::opencash::model::Account, id_sqlite, A >::
  uuid (A::table_name, "\"uuid\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::model::Account, id_sqlite, A >::name_type_
  query_columns< ::opencash::model::Account, id_sqlite, A >::
  name (A::table_name, "\"name\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::model::Account, id_sqlite, A >::description_type_
  query_columns< ::opencash::model::Account, id_sqlite, A >::
  description (A::table_name, "\"description\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::model::Account, id_sqlite, A >::type_type_
  query_columns< ::opencash::model::Account, id_sqlite, A >::
  type (A::table_name, "\"type\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::model::Account, id_sqlite, A >::parent_type_
  query_columns< ::opencash::model::Account, id_sqlite, A >::
  parent (A::table_name, "\"parent\"", 0);
}

#include <generated/Account-odb.ixx>

#include <odb/post.hxx>

#endif // ACCOUNT_ODB_HXX
