/************************************************************************
 *  created:    10.4.2008  19:28
 *  filename:   ExpImpStlClasses.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __EXPIMPSTLCLASSES_H__
#define __EXPIMPSTLCLASSES_H__

#define EXPORT_STL_STRING( dllmacro) \
  template class dllmacro std::allocator< char >; \
  template class dllmacro std::basic_string<char, \
  std::char_traits< char >, std::allocator< char > >;


#define EXPORT_STL_VECTOR( dllmacro, vectype ) \
  template class dllmacro std::allocator< vectype >; \
  template class dllmacro std::vector<vectype, \
      std::allocator< vectype > >;

#define EXPORT_STL_LIST( dllmacro, listtype ) \
  template class dllmacro std::allocator< listtype >; \
  template class dllmacro std::list<listtype, \
      std::allocator< listtype > >;

#define EXPORT_STL_SET( dllmacro, settype ) \
  template class dllmacro std::allocator< settype >; \
  template struct dllmacro std::less< settype >; \
  template class dllmacro std::allocator< \
      std::_Tree_nod<std::_Tset_traits<settype,std::less<settype>, \
      std::allocator<settype>,false> > >; \
  template class dllmacro std::allocator<  \
      std::_Tree_ptr<std::_Tset_traits<settype,std::less<settype>, \
      std::allocator<settype>,false> > >; \
  template class dllmacro std::_Tree_ptr< \
      std::_Tset_traits<settype,std::less<settype>, \
      std::allocator<settype>,false> >; \
  template class dllmacro std::_Tree_nod< \
      std::_Tset_traits<settype,std::less<settype>, \
      std::allocator<settype>,false> >; \
  template class dllmacro std::_Tree_val< \
      std::_Tset_traits<settype,std::less<settype>, \
      std::allocator<settype>,false> >; \
  template class dllmacro std::set< settype, std::less< settype >, \
      std::allocator< settype > >; 

#define EXPORT_STL_MAP( dllmacro, mapkey, mapvalue ) \
  template class dllmacro std::allocator<mapvalue>; \
  template struct dllmacro std::pair< mapkey,mapvalue >; \
  template class dllmacro std::allocator< \
  std::pair<const mapkey,mapvalue> >; \
  template struct dllmacro std::less< mapkey >; \
  template class dllmacro std::allocator< \
  std::_Tree_ptr<std::_Tmap_traits<mapkey,mapvalue,std::less<mapkey>, \
  std::allocator<std::pair<const mapkey,mapvalue> >,false> > >; \
  template class dllmacro std::allocator< \
  std::_Tree_nod<std::_Tmap_traits<mapkey,mapvalue,std::less<mapkey>, \
  std::allocator<std::pair<const mapkey,mapvalue> >,false> > >; \
  template class dllmacro std::_Tree_nod< \
  std::_Tmap_traits<mapkey,mapvalue,std::less<mapkey>, \
  std::allocator<std::pair<const mapkey,mapvalue> >,false> >; \
  template class dllmacro std::_Tree_ptr< \
  std::_Tmap_traits<mapkey,mapvalue,std::less<mapkey>, \
  std::allocator<std::pair<const mapkey,mapvalue> >,false> >; \
  template class dllmacro std::_Tree_val< \
  std::_Tmap_traits<mapkey,mapvalue,std::less<mapkey>, \
  std::allocator<std::pair<const mapkey,mapvalue> >,false> >; \
  template class dllmacro std::map< \
  mapkey, mapvalue, std::less< mapkey >, \
  std::allocator<std::pair<const mapkey,mapvalue> > >;

#endif // __EXPIMPSTLCLASSES_H__