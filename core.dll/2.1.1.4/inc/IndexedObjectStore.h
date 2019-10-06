#ifndef __INDEXED_OBJECT_STORE_H__
#define __INDEXED_OBJECT_STORE_H__

#include <map>
#include <utility>

template<typename TIndex, typename TObject>
class TIndexedObjectStore
{
public:
  typedef std::map<TIndex, TObject> TStoreType;

private:
  TIndex m_index;  
  TStoreType m_store;
  TStoreType m_deletedStore;

public:
  TIndexedObjectStore() : m_index()
  { }

  ~TIndexedObjectStore()
  { }

  const TStoreType& store() const { return m_store; }
  const TStoreType& deletedStore() const { return m_deletedStore; }

  bool insert(const TObject& val, TIndex& elemIdx)
  {
    std::pair<TStoreType::iterator, bool> ret = m_store.insert(std::make_pair(m_index, val));
    if(ret.second == false)
      return false;

    elemIdx = m_index;
    m_index++;
    return true;
  }

  bool update(const TIndex& elemIdx, const TObject& val)
  {
    if(!elemExists(elemIdx))
      return false;

    m_store[elemIdx] = val;
    return true;
  }

  bool erase(const TIndex& elemIdx)
  {
    TStoreType::iterator it = m_store.find(elemIdx);
    if(it == m_store.end())
      return false;

    std::pair<TStoreType::iterator, bool> ret = m_deletedStore.insert(std::make_pair(it->first, it->second));
    if(ret.second == false)
      return false;

    m_store.erase(it);
    return true;
  }

  bool find_elem(const TIndex& elemIdx, TObject& retVal)
  {
    TStoreType::iterator it = m_store.find(elemIdx);
    if(it == m_store.end())
      return false;

    retVal = it->second;
    return true;
  }

  bool elemExists(const TIndex& elemIdx)
  {
    TStoreType::iterator it = m_store.find(elemIdx);
    if(it == m_store.end())
      return false;

    return true;
  }

  void clear()
  {
    m_store.clear();
    m_deletedStore.clear();
    m_index = TIndex();
  }

  void clearDeletedStore()
  {
    m_deletedStore.clear();
  }

private:
  TIndexedObjectStore(const TIndexedObjectStore& s) {}
  TIndexedObjectStore& operator = (const TIndexedObjectStore& s) { return *this; }
};

#endif //__INDEXED_OBJECT_STORE_H__