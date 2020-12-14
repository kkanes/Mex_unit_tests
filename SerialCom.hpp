//============================================================================
// Name        : SerialCom.hpp
// Author      : Willi Penner
//
// Description : SerialCom header file. It contains the declaration of the
//               ISerialCom interface and the SerialCom class
//============================================================================
#ifndef SERIALCOM_HPP_INCLUDED
#define SERIALCOM_HPP_INCLUDED

#include <string>


#ifdef _WIN32
    #include <windows.h>
#else
	#include <iostream>
#endif


using namespace std;

/**
 *
 * \class SerialCom
 *
 *  \brief Interface for a serial connection via serial port.
 *  The implementation of this communication requires the
 *  configuration setting of the Pololu as "USB Dual Port"
 *  (see also https://www.pololu.com/docs/0J40/5.a).
 *
 */
class ISerialCom {
public:
	virtual ~ISerialCom(){};


    /** \brief Used to initiate the SerialCom object with port name and baud rate.
     *  The function puts the object in the same state as the constructor with transfer parameters.
     *  It can be used to change the port name and the baud rate of a SerialCom object.
     *
     *  \param portName : The port name is used to open a serial connection via the port name for the controller specified by the operating system.
     *  \param baudRate : The baud rate determines the transmission speed at which communication between the PC and controller takes place.
     */
    virtual void initSerialCom(const char* portName, unsigned short baudRate) = 0;

    /** \brief Uses the set port name and the baud rate of the class to open a serial connection.
     *  If the opening is successful, the value in "port_" stands for the open connection and
     *  can be used for communication.
     *
     *  \return Returns TRUE on successful opening of a serial connection, otherwise it returns FALSE.
     */
    virtual bool openSerialCom() = 0;

    /** \brief Closes a serial connection.
     *
     *  \return Returns TRUE on successful closing of a serial connection, otherwise it returns FALSE.
     */
    virtual bool closeSerialCom() = 0;

    /** \brief "writeSerialCom" is used to write commands to the controller via the open serial connection.
     *
     * \param command[] : Contains the command to be sent (size of 1, 2 or 4 bytes, depending on the command).
     * \param sizeCommand : Contains the size of the command (1, 2 or 4).
     * \param response : If the command to be sent expects a return value from the controller, the writeSerialCom is given a pointer to a response array. This can be 1 or 2 bytes in size. If no return value is expected, the pointer is NULL.
     * \param sizeResponse : Contains the size of the command (1 or 2, in case of no expected return value it is 0).
     *
     * \return Returns TRUE on successful writing to a serial connection, otherwise it returns FALSE.
     */
    virtual bool writeSerialCom(unsigned char command[], unsigned short sizeCommand, unsigned char *response, unsigned short sizeResponse) = 0;
};




class SerialBase : public ISerialCom{
	protected:
		bool  isSerialComOpen_ = false;
		const char* portName_ = nullptr;
		unsigned short baudRate_ = 0;
};


#ifdef _WIN32
	class SerialComWIN32 : public SerialBase{
		public:
				 SerialComWIN32(const char* portName="COM0", unsigned short baudRate=9600);
			void initSerialCom (const char* portName="COM0", unsigned short baudRate=9600);
			bool openSerialCom ();
			bool closeSerialCom();
			bool writeSerialCom(unsigned char command[], unsigned short sizeCommand, unsigned char *response, unsigned short sizeResponse);
	        HANDLE getPort();
		protected:
	        HANDLE port_;
	};
#else
	class SerialComLINUX : public SerialBase{
		public:
				 SerialComLINUX(const char* portName="/dev/ttyACM0", unsigned short baudRate=9600);
		    void initSerialCom(const char* portName="/dev/ttyACM0", unsigned short baudRate=9600);
		    bool openSerialCom();
		    bool closeSerialCom();
		    bool writeSerialCom(unsigned char command[], unsigned short sizeCommand, unsigned char *response, unsigned short sizeResponse);
		    int  getPort();
		protected:
		    int port_;
	};
#endif


#ifdef _WIN32
	class SerialCom : public SerialComWIN32{
	public:
		SerialCom(const char* portName="COM0",
				unsigned short baudRate=9600) : SerialComWIN32(portName,baudRate){};
	};
#else
	class SerialCom : public SerialComLINUX{
	public:
		SerialCom(const char* portName="/dev/ttyACM0",
				unsigned short baudRate=9600) : SerialComLINUX(portName,baudRate){};
		~SerialCom(){
				this->closeSerialCom();
		};
	};
#endif


/**
 *
 * \class IException
 *
 * \brief Interface for exceptions to be overwritten
 * by the derived classes.
 *
 */
class IException{
	public:

		/**
		 *
		 * \return string error messages
		 *
		 */
		virtual string getMsg() = 0;
};


/**
 *
 * \class ExceptionSerialCom
 *
 * \brief Exception class for class \ref SerialCom
 *
 *
 */
class ExceptionSerialCom : public IException{
	public:

		/**
		 *
		 * \brief Constructor of the class
		 *
		 * \param string error message
		 *
		 */
		ExceptionSerialCom(string msg){
			msg_ = string("ExceptionSerialCom::") + msg;
		};

		/**
		 * Returns the error message.
		 *
		 * \return string containing the error message
		 *
		 */
		string getMsg(){return msg_;}
	protected:
		string msg_;
	private:
		ExceptionSerialCom(){};
};


#endif // SERIALCOM_HPP_INCLUDED
