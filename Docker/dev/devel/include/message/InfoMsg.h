// Generated by gencpp from file message/InfoMsg.msg
// DO NOT EDIT!


#ifndef MESSAGE_MESSAGE_INFOMSG_H
#define MESSAGE_MESSAGE_INFOMSG_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace message
{
template <class ContainerAllocator>
struct InfoMsg_
{
  typedef InfoMsg_<ContainerAllocator> Type;

  InfoMsg_()
    : x(0.0)
    , y(0.0)
    , otherspos()
    , possact()
    , timeleft(0.0)  {
    }
  InfoMsg_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , otherspos(_alloc)
    , possact(_alloc)
    , timeleft(0.0)  {
  (void)_alloc;
    }



   typedef float _x_type;
  _x_type x;

   typedef float _y_type;
  _y_type y;

   typedef std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> _otherspos_type;
  _otherspos_type otherspos;

   typedef std::vector<int16_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int16_t>> _possact_type;
  _possact_type possact;

   typedef float _timeleft_type;
  _timeleft_type timeleft;





  typedef boost::shared_ptr< ::message::InfoMsg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::message::InfoMsg_<ContainerAllocator> const> ConstPtr;

}; // struct InfoMsg_

typedef ::message::InfoMsg_<std::allocator<void> > InfoMsg;

typedef boost::shared_ptr< ::message::InfoMsg > InfoMsgPtr;
typedef boost::shared_ptr< ::message::InfoMsg const> InfoMsgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::message::InfoMsg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::message::InfoMsg_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::message::InfoMsg_<ContainerAllocator1> & lhs, const ::message::InfoMsg_<ContainerAllocator2> & rhs)
{
  return lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.otherspos == rhs.otherspos &&
    lhs.possact == rhs.possact &&
    lhs.timeleft == rhs.timeleft;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::message::InfoMsg_<ContainerAllocator1> & lhs, const ::message::InfoMsg_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace message

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::message::InfoMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::message::InfoMsg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::message::InfoMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::message::InfoMsg_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::message::InfoMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::message::InfoMsg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::message::InfoMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "74243b5379e1c0f977f139ace36782e4";
  }

  static const char* value(const ::message::InfoMsg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x74243b5379e1c0f9ULL;
  static const uint64_t static_value2 = 0x77f139ace36782e4ULL;
};

template<class ContainerAllocator>
struct DataType< ::message::InfoMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "message/InfoMsg";
  }

  static const char* value(const ::message::InfoMsg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::message::InfoMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 x\n"
"float32 y\n"
"float32[] otherspos\n"
"int16[] possact\n"
"float32 timeleft\n"
;
  }

  static const char* value(const ::message::InfoMsg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::message::InfoMsg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.otherspos);
      stream.next(m.possact);
      stream.next(m.timeleft);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct InfoMsg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::message::InfoMsg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::message::InfoMsg_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    Printer<float>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<float>::stream(s, indent + "  ", v.y);
    s << indent << "otherspos[]" << std::endl;
    for (size_t i = 0; i < v.otherspos.size(); ++i)
    {
      s << indent << "  otherspos[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.otherspos[i]);
    }
    s << indent << "possact[]" << std::endl;
    for (size_t i = 0; i < v.possact.size(); ++i)
    {
      s << indent << "  possact[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.possact[i]);
    }
    s << indent << "timeleft: ";
    Printer<float>::stream(s, indent + "  ", v.timeleft);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MESSAGE_MESSAGE_INFOMSG_H