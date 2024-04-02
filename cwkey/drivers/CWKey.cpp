#include <QHostInfo>
#include "CWKey.h"
#include "core/debug.h"

MODULE_IDENTIFICATION("qlog.cwkey.driver.cwkey");

CWKey::CWKey(CWKeyModeID mode, qint32 defaultWPM, QObject *parent) :
    QObject(parent),
    keyMode(mode),
    defaultWPMSpeed(defaultWPM),
    stopSendingCap(false),
    echoCharsCap(false),
    rigMustConnectedCap(false),
    canSetKeySpeed(false)
{
    FCT_IDENTIFICATION;
    qCDebug(function_parameters) << mode << defaultWPM;
}

void CWKey::printKeyCaps()
{
    FCT_IDENTIFICATION;

    qCDebug(runtime) << "stopSendingCap" << stopSendingCap;
    qCDebug(runtime) << "echoCharsCap" << echoCharsCap;
    qCDebug(runtime) << "rigMustConnectedCap" << rigMustConnectedCap;
    qCDebug(runtime) << "canSetKeySpeed" << canSetKeySpeed;
}

CWKey::CWKeyTypeID CWKey::intToTypeID(int i)
{
    FCT_IDENTIFICATION;

    if ( i < DUMMY_KEYER || i > LAST_MODEL )
    {
        qCWarning(runtime) << "Unknown Mode" << i;
        return LAST_MODEL;
    }
    return static_cast<CWKey::CWKeyTypeID>(i);
}

CWKey::CWKeyModeID CWKey::intToModeID(int i)
{
    FCT_IDENTIFICATION;

    if ( i < SINGLE_PADDLE || i > LAST_MODE )
    {
        qCWarning(runtime) << "Unknown Mode" << i;
        return LAST_MODE;
    }
    return static_cast<CWKey::CWKeyModeID>(i);
}

bool CWKey::isNetworkKey(const CWKeyTypeID &type)
{
    FCT_IDENTIFICATION;

    bool ret = (type == CWDAEMON_KEYER
                || type == FLDIGI_KEYER );

    qCDebug(runtime) << ret;
    return ret;
}

QDataStream& operator>>(QDataStream &in, CWKey::CWKeyModeID &v)
{
    int i;
    in >> i;
    v = static_cast<CWKey::CWKeyModeID>(i);
    return in;
}

QDataStream& operator<<(QDataStream &out, const CWKey::CWKeyModeID &v)
{
    out << static_cast<int>(v);
    return out;
}

QDataStream& operator>>(QDataStream &in, CWKey::CWKeyTypeID &v)
{
    int i;
    in >> i;
    v = static_cast<CWKey::CWKeyTypeID>(i);
    return in;
}

QDataStream& operator<<(QDataStream &out, const CWKey::CWKeyTypeID &v)
{
    out << static_cast<int>(v);
    return out;
}

CWKeySerialInterface::CWKeySerialInterface(const QString &portName,
                                           const qint32 baudrate,
                                           const qint32 timeout) :
    timeout(timeout)
{
    FCT_IDENTIFICATION;

    qCDebug(function_parameters) << portName << baudrate << timeout;

    serial.setPortName(portName);

    if ( ! serial.setBaudRate(baudrate, QSerialPort::AllDirections) )
    {
        qWarning() << "Cannot set Baudrate for Serial port";
    }
    if ( ! serial.setDataBits(QSerialPort::Data8) )
    {
        qWarning() << "Cannot set Data Bits for Serial port";
    }
    if ( ! serial.setParity(QSerialPort::NoParity) )
    {
        qWarning() << "Cannot set Parity for Serial port";
    }
    if ( ! serial.setFlowControl(QSerialPort::NoFlowControl) )
    {
        qWarning() << "Cannot set Flow Control for Serial port";
    }
    if ( ! serial.setStopBits(QSerialPort::TwoStop) )
    {
        qWarning() << "Cannot set Stop Bits for Serial port";
    }
}

qint64 CWKeySerialInterface::sendDataAndWait(const QByteArray &data)
{
    FCT_IDENTIFICATION;

    qCDebug(runtime) << "Waiting for Port Mutex";
    QMutexLocker locker(&portMutex);

    if ( ! serial.isOpen() )
    {
        qCDebug(runtime) << "Serial port is not opened";
        return - 1;
    }

    qCDebug(runtime) << "\t<<<<<< SND Sync: " << data;

    qint64 ret = serial.write(data);

    if ( ret == -1 )
    {
        qWarning() << "Serial Port Error: " << serial.errorString() << serial.error();
    }
    else
    {
        if ( !serial.waitForBytesWritten(timeout) )
        {
            qCDebug(runtime) << "Serial Port Timeout";
            return -1;
        }
    }
    return ret;
}

qint64 CWKeySerialInterface::receiveDataAndWait(QByteArray &data)
{
    FCT_IDENTIFICATION;

    qCDebug(runtime) << "Waiting for Port Mutex";
    QMutexLocker locker(&portMutex);

    if ( ! serial.isOpen() )
    {
        qCDebug(runtime) << "Serial port is not opened";
        return - 1;
    }

    if ( serial.waitForReadyRead(timeout))
    {
        data = serial.readAll();
        while ( serial.waitForReadyRead(10) )
        {
            data += serial.readAll();
        }
    }
    else
    {
        qCDebug(runtime) << "Serial Port Timeout";
        return -1;
    }

    qCDebug(runtime) << "\t>>>>>> RCV Sync: " << data;

    return data.size();
}

qint64 CWKeySerialInterface::writeAsyncData(const QByteArray &data)
{
    FCT_IDENTIFICATION;

    qCDebug(runtime) << "Waiting for Port Mutex";
    QMutexLocker locker(&portMutex);

    if ( ! serial.isOpen() )
    {
        qCDebug(runtime) << "Serial port is not opened";
        return - 1;
    }

    qCDebug(runtime) << "\t<<<<<< SND Async:" << data;

    qint64 ret = serial.write(data);

    if ( ret == -1 )
    {
        qWarning() << "Serial Port Error: " << serial.errorString() << serial.error();
    }

    return ret;
}

CWKeyUDPInterface::CWKeyUDPInterface(const QString &hostname,
                                     const quint16 port) :
    CWKeyIPInterface(hostname, port)
{
    FCT_IDENTIFICATION;
}

qint64 CWKeyUDPInterface::sendData(const QByteArray &data)
{
    FCT_IDENTIFICATION;

    qCDebug(runtime) << "\t<<<<<< SND: " << data << "(" << serverName << "port:" << port << ")";

    return socket.writeDatagram(data, serverName, port);
}

bool CWKeyUDPInterface::isSocketReady()
{
    FCT_IDENTIFICATION;

    qCDebug(runtime) << hasIPAddress;

    return hasIPAddress;
}

CWKeyIPInterface::CWKeyIPInterface(const QString &hostname,
                                   const quint16 port) :
    serverName(QHostAddress()),
    port(port),
    hasIPAddress(false)
{
    FCT_IDENTIFICATION;

    qCDebug(function_parameters) << hostname << port;

    QHostInfo info = QHostInfo::fromName(hostname);

    if (info.error() == QHostInfo::NoError)
    {
        serverName = QHostAddress(info.addresses().at(0));
        qCDebug(runtime) << "Using IP address" << serverName;
        hasIPAddress = true;
    }
}
