#include <bits/stdc++.h>
#define fastIo                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
using namespace std;
class NetworkAddress
{
public:
    int netId1, netId2, netId3, hostId, CIDRPrefix;
    NetworkAddress() {}
    NetworkAddress(int _netId1, int _netId2, int _netId3, int _hostId, int _CIDRPrefix)
    {
        netId1 = _netId1;
        netId2 = _netId2;
        netId3 = _netId3;
        hostId = _hostId;
        CIDRPrefix = _CIDRPrefix;
    }
    string to_str()
    {
        return to_string(netId1) + "." + to_string(netId2) + "." + to_string(netId3) + "." + to_string(hostId) + "/" + to_string(CIDRPrefix);
    }
    string to_str_without_prefix()
    {
        return to_string(netId1) + "." + to_string(netId2) + "." + to_string(netId3) + "." + to_string(hostId);
    }
    void display()
    {
        cout << netId1 << "." << netId2 << "." << netId3 << "." << hostId << "/" << CIDRPrefix << endl;
    }
    void displayWithoutNewline()
    {
        cout << netId1 << "." << netId2 << "." << netId3 << "." << hostId << "/" << CIDRPrefix;
    }
};
class Device;
class Interface
{
public:
    string name;
    NetworkAddress ipAddress, subMask, defaultGateway;
    Device *connectedDevice;

    Interface() {}
    Interface(string _name)
    {
        name = _name;
    }
};
class Device
{
public:
    string name;
    vector<Interface> serial, fastEthernet;
    Device() {}
    Device(string _name)
    {
        name = _name;
    }
    bool operator==(const Device &d) const
    {
        return (name == d.name);
    }
};
class DeviceHashFunction
{
public:
    // name is returned as hash function
    size_t operator()(const Device &d) const
    {
        return (hash<string>()(d.name));
    }
};
class Network
{
public:
    string name;
    Device device1, device2;
    NetworkAddress ipAddress, mask, rangeStarting, rangeEnding, curAvailableAddress;

    int host;
    Network() {}
    Network(Device _device1, Device _device2)
    {
        device1 = _device1;
        device2 = _device2;
    }
    Network(Device _device1, Device _device2, int _host)
    {
        device1 = _device1;
        device2 = _device2;
        host = _host;
    }
};
NetworkAddress addNetId(NetworkAddress netAddress, int numOfNetIdToAdd)
{
    int netId1 = netAddress.netId1, netId2 = netAddress.netId2, netId3 = netAddress.netId3, hostId = netAddress.hostId;
    int newNetId1, newNetId2, newNetId3, newHostId;
    int divideBy = 256;

    newHostId = hostId + numOfNetIdToAdd;
    newNetId3 = netId3 + (newHostId / divideBy);
    newNetId2 = netId2 + (newNetId3 / divideBy);
    newNetId1 = netId1 + (newNetId2 / divideBy);

    newHostId = newHostId % divideBy;
    newNetId3 = newNetId3 % divideBy;
    newNetId2 = newNetId2 % divideBy;

    netAddress.netId1 = newNetId1;
    netAddress.netId2 = newNetId2;
    netAddress.netId3 = newNetId3;
    netAddress.hostId = newHostId;
    return netAddress;
}

class DeviceConnection
{
public:
    Device device1, device2;
    Interface interface;
    DeviceConnection() {}
    DeviceConnection(Device _device1, Device _device2, Interface _interface)
    {
        device1 = _device1;
        device2 = _device2;
        interface = _interface;
    }
};
int stringContains(string key, string fullString)
{
    if (fullString.find(key) != std::string::npos)
        return 1;
    return 0;
}
int isPc(Device device)
{
    return stringContains("PC", device.name);
}
void displayAddressingTable(vector<Device> devices)
{

    int setwVal = 20;
    cout << left << setw(setwVal - 5) << "Device";
    cout << left << setw(setwVal - 5) << "Interface";
    cout << left << setw(setwVal) << "Connected Device";
    cout << left << setw(setwVal) << "IP Address";
    cout << left << setw(setwVal) << "Submask";
    cout << left << setw(setwVal) << "Default Gateway";
    cout << endl;
    for (int i = 0; i < devices.size(); i++)
    {
        Device dev = devices[i];
        for (int j = 0; j < dev.serial.size(); j++)
        {
            if (j == 0)
                cout << left << setw(setwVal - 5) << dev.name;
            else
                cout << left << setw(setwVal - 5) << "";
            cout << left << setw(setwVal - 5) << dev.serial[j].name;
            cout << left << setw(setwVal) << dev.serial[j].connectedDevice->name;
            cout << left << setw(setwVal) << dev.serial[j].ipAddress.to_str();
            cout << left << setw(setwVal) << dev.serial[j].subMask.to_str();

            if (!stringContains("PC", dev.name))
                cout << left << setw(setwVal) << "N/A" << endl;
            else
                cout << left << setw(setwVal) << dev.serial[j].defaultGateway.to_str() << endl;
        }
        for (int j = 0; j < dev.fastEthernet.size(); j++)
        {
            if (j == 0 and dev.serial.size() == 0)
                cout << left << setw(setwVal - 5) << dev.name;
            else
                cout << left << setw(setwVal - 5) << "";
            cout << left << setw(setwVal - 5) << dev.fastEthernet[j].name;
            cout << left << setw(setwVal) << dev.fastEthernet[j].connectedDevice->name;
            cout << left << setw(setwVal) << dev.fastEthernet[j].ipAddress.to_str();
            cout << left << setw(setwVal) << dev.fastEthernet[j].subMask.to_str();

            if (!stringContains("PC", dev.name))
                cout << left << setw(setwVal) << "N/A" << endl;
            else
                cout << left << setw(setwVal) << dev.fastEthernet[j].defaultGateway.to_str() << endl;
        }
        cout << endl;
    }
}
string getSerialConnName(int numOfSerialConn)
{
    int a = 2;
    string se1 = "0", se2, se3;
    if (numOfSerialConn % 2 == 1)
    {
        a = 1;
        se3 = "0";
    }
    else
    {
        se3 = "1";
    }
    int term = (numOfSerialConn - a) / 2 + 1;
    se2 = to_string(term - 1);
    return "se" + se1 + "/" + se2 + "/" + se3;
}
map<string, int> visitedNet;
Device dfs(map<string, vector<Network>> devNetMap, Device curDev, Device &destEntryDev, Device &destEntryPrevDev, Network destNet)
{
    string curDevName = curDev.name;

    if (destNet.device1.name == curDevName)
    {
        destEntryDev = destNet.device1;
        return destEntryDev;
    }
    else if (destNet.device2.name == curDevName)
    {
        destEntryDev = destNet.device2;
        return destEntryDev;
    }

    vector<Network> netVec = devNetMap[curDevName];
    for (int i = 0; i < netVec.size(); i++)
    {
        if (destEntryDev.name != "No device found")
            return destEntryDev;
        Network net = netVec[i];
        if (isPc(net.device1) || isPc(net.device2))
        {
            visitedNet[net.name] = 1;
            continue;
        }
        if (visitedNet[net.name])
            continue;
        if (net.device1.name == curDevName)
        {
            visitedNet[net.name] = 1;
            destEntryPrevDev = curDev;
            dfs(devNetMap, net.device2, destEntryDev, destEntryPrevDev, destNet);
        }
        else if (net.device2.name == curDevName)
        {
            visitedNet[net.name] = 1;
            destEntryPrevDev = curDev;
            dfs(devNetMap, net.device1, destEntryDev, destEntryPrevDev, destNet);
        }
    }

    return destEntryDev;
}

int main()
{
    fastIo;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int line;
    cin >> line;
    int host;
    string dev1, dev2;
    vector<Network> netWithHost, netWithoutHost, netMerged;
    unordered_set<Device, DeviceHashFunction> uniqueDevices;
    for (int i = 0; i < line; i++)
    {
        cin >> dev1 >> dev2;
        Network net;
        Device D1, D2;
        if (stringContains("PC", dev1))
        {
            cin >> host;
            D1 = Device(dev1);
            D2 = Device(dev2);
            net = Network(D1, D2, host);
            netWithHost.push_back(net);
        }
        else if (stringContains("PC", dev2))
        {
            cin >> host;
            D1 = Device(dev1);
            D2 = Device(dev2);
            net = Network(D1, D2, host);
            netWithHost.push_back(net);
        }
        else
        {
            D1 = Device(dev1);
            D2 = Device(dev2);
            net = Network(D1, D2);
            netWithoutHost.push_back(net);
        }
        uniqueDevices.insert(D1);
        uniqueDevices.insert(D2);
    }

    int netId1, netId2, netId3, hostId, CIDRPrefix;
    NetworkAddress networkAddress = NetworkAddress();

    char netAddressStr[20];
    cin >> netAddressStr;
    sscanf(netAddressStr, "%d.%d.%d.%d/%d", &networkAddress.netId1, &networkAddress.netId2, &networkAddress.netId3, &networkAddress.hostId, &networkAddress.CIDRPrefix);

    // Sorting in descending order by host
    sort(netWithHost.begin(), netWithHost.end(), [](const auto &lhs, const auto &rhs)
         { return lhs.host > rhs.host; });

    for (int i = 0; i < netWithHost.size(); i++)
    {
        Network net = netWithHost[i];

        // Calculating IP Address
        float logOfHostFloat = log2(net.host);
        int logOfHostFinal;
        if (floor(logOfHostFloat) == ceil(logOfHostFloat))
            logOfHostFinal = int(logOfHostFloat);
        else
            logOfHostFinal = int(logOfHostFloat) + 1;

        networkAddress.CIDRPrefix = 32 - logOfHostFinal;

        // Calculating Mask
        string CIDRPrefixBin = string(networkAddress.CIDRPrefix, '1') + string(32 - networkAddress.CIDRPrefix, '0');
        int ipAddressArr[4];
        for (int k = 0, ipAddressArrIndex = 0; k <= 24; k += 8, ipAddressArrIndex++)
        {
            unsigned long partOfMask = std::bitset<8>(CIDRPrefixBin.substr(k, k + 8)).to_ulong();
            ipAddressArr[ipAddressArrIndex] = int(partOfMask);
        }
        net.mask = NetworkAddress(ipAddressArr[0], ipAddressArr[1], ipAddressArr[2], ipAddressArr[3], networkAddress.CIDRPrefix);

        if (i == 0)
        {
            net.ipAddress = NetworkAddress(networkAddress.netId1, networkAddress.netId2, networkAddress.netId3, networkAddress.hostId, networkAddress.CIDRPrefix);
        }
        else
        {
            NetworkAddress tempNetAd = addNetId(netWithHost[i - 1].rangeEnding, 1);
            tempNetAd.CIDRPrefix = networkAddress.CIDRPrefix;
            net.ipAddress = tempNetAd;
        }
        // Calculating Range
        net.rangeStarting = net.ipAddress;
        net.rangeEnding = addNetId(net.rangeStarting, pow(2, logOfHostFinal) - 1);

        netWithHost[i] = net;
    }

    for (int i = 0; i < netWithoutHost.size(); i++)
    {
        Network net = netWithoutHost[i];

        // Calculating IP Address
        float logOfHostFloat = log2(4);
        int logOfHostFinal;
        if (floor(logOfHostFloat) == ceil(logOfHostFloat))
            logOfHostFinal = int(logOfHostFloat);
        else
            logOfHostFinal = int(logOfHostFloat) + 1;

        networkAddress.CIDRPrefix = 32 - logOfHostFinal;

        if (i == 0)
        {
            NetworkAddress tempNetAd = addNetId(netWithHost[netWithHost.size() - 1].rangeEnding, 1);
            tempNetAd.CIDRPrefix = networkAddress.CIDRPrefix;
            net.ipAddress = tempNetAd;
        }
        else
        {
            NetworkAddress tempNetAd = addNetId(netWithoutHost[i - 1].rangeEnding, 1);
            tempNetAd.CIDRPrefix = networkAddress.CIDRPrefix;
            net.ipAddress = tempNetAd;
        }

        // Calculating Mask
        string CIDRPrefixBin = string(networkAddress.CIDRPrefix, '1') + string(32 - networkAddress.CIDRPrefix, '0');
        int ipAddressArr[4];
        for (int k = 0, ipAddressArrIndex = 0; k <= 24; k += 8, ipAddressArrIndex++)
        {
            unsigned long partOfMask = std::bitset<8>(CIDRPrefixBin.substr(k, k + 8)).to_ulong();
            ipAddressArr[ipAddressArrIndex] = int(partOfMask);
        }
        net.mask = NetworkAddress(ipAddressArr[0], ipAddressArr[1], ipAddressArr[2], ipAddressArr[3], networkAddress.CIDRPrefix);

        // Calculating Range
        net.rangeStarting = net.ipAddress;
        net.rangeEnding = addNetId(net.rangeStarting, pow(2, logOfHostFinal) - 1);

        netWithoutHost[i] = net;
    }

    copy(netWithHost.begin(), netWithHost.end(), back_inserter(netMerged));
    copy(netWithoutHost.begin(), netWithoutHost.end(), back_inserter(netMerged));

    for (int i = 0; i < netMerged.size(); i++)
    {
        netMerged[i].curAvailableAddress = netMerged[i].ipAddress;
        netMerged[i].name = "Net " + to_string(i + 1);
        cout << netMerged[i].name << ":" << endl;
        cout << "Connection:  " << netMerged[i].device1.name << " - " << netMerged[i].device2.name << endl;
        cout << "IP Address: " << netMerged[i].ipAddress.to_str() << endl;
        cout << "Mask: " << netMerged[i].mask.to_str() << endl;
        cout << "Range: " << netMerged[i].rangeStarting.to_str() << " - " << netMerged[i].rangeEnding.to_str() << endl;
        cout << endl;
    }

    vector<Device> tempUniqueDeviceVec, uniqueDeviceVec;
    int uniqueDeviceInserted[uniqueDevices.size()] = {0};
    for (auto uniqueDevice : uniqueDevices)
    {
        tempUniqueDeviceVec.push_back(uniqueDevice);
    }
    for (int i = 0; i < tempUniqueDeviceVec.size(); i++)
    {
        if (!stringContains("PC", tempUniqueDeviceVec[i].name))
        {
            uniqueDeviceVec.push_back(tempUniqueDeviceVec[i]);
            uniqueDeviceInserted[i] = 1;
        }
    }
    for (int i = 0; i < tempUniqueDeviceVec.size(); i++)
    {
        if (!uniqueDeviceInserted[i])
        {
            uniqueDeviceVec.push_back(tempUniqueDeviceVec[i]);
        }
    }

    vector<DeviceConnection> devConVec;
    for (int i = 0; i < uniqueDeviceVec.size(); i++)
    {
        for (int j = 0; j < netMerged.size(); j++)
        {

            if (uniqueDeviceVec[i] == netMerged[j].device1)
            {

                Device oppositeDevice = netMerged[j].device2;
                if (stringContains("PC", oppositeDevice.name) || stringContains("PC", uniqueDeviceVec[i].name))
                {
                    Interface interface = Interface("fa0/" + to_string(uniqueDeviceVec[i].fastEthernet.size()));
                    netMerged[j].curAvailableAddress = addNetId(netMerged[j].curAvailableAddress, 1);

                    interface.ipAddress = netMerged[j].curAvailableAddress;
                    interface.subMask = netMerged[j].mask;

                    // Default gateway calculation
                    if (stringContains("PC", uniqueDeviceVec[i].name))
                    {
                        for (int l = 0; l < uniqueDeviceVec.size(); l++)
                        {
                            if (oppositeDevice.name == uniqueDeviceVec[l].name)
                            {
                                for (int m = 0; m < uniqueDeviceVec[l].fastEthernet.size(); m++)
                                {
                                    if (interface.name == uniqueDeviceVec[l].fastEthernet[m].name)
                                    {

                                        interface.defaultGateway = uniqueDeviceVec[l].fastEthernet[m].ipAddress;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    interface.connectedDevice = &netMerged[j].device2;
                    devConVec.push_back(DeviceConnection(uniqueDeviceVec[i], netMerged[j].device2, interface));
                    uniqueDeviceVec[i].fastEthernet.push_back(interface);
                }
                else
                {

                    Interface interface = Interface(getSerialConnName(uniqueDeviceVec[i].serial.size() + 1));
                    netMerged[j].curAvailableAddress = addNetId(netMerged[j].curAvailableAddress, 1);
                    interface.ipAddress = netMerged[j].curAvailableAddress;
                    interface.subMask = netMerged[j].mask;
                    interface.connectedDevice = &netMerged[j].device2;
                    devConVec.push_back(DeviceConnection(uniqueDeviceVec[i], netMerged[j].device2, interface));
                    uniqueDeviceVec[i].serial.push_back(interface);
                }
            }
            else if (uniqueDeviceVec[i] == netMerged[j].device2)
            {
                Device oppositeDevice = netMerged[j].device1;
                if (stringContains("PC", oppositeDevice.name) || stringContains("PC", uniqueDeviceVec[i].name))
                {
                    Interface interface = Interface("fa0/" + to_string(uniqueDeviceVec[i].fastEthernet.size()));

                    netMerged[j].curAvailableAddress = addNetId(netMerged[j].curAvailableAddress, 1);
                    interface.ipAddress = netMerged[j].curAvailableAddress;
                    interface.subMask = netMerged[j].mask;
                    // Default gateway calculation
                    if (stringContains("PC", uniqueDeviceVec[i].name))
                    {
                        for (int l = 0; l < uniqueDeviceVec.size(); l++)
                        {
                            if (oppositeDevice.name == uniqueDeviceVec[l].name)
                            {
                                for (int m = 0; m < uniqueDeviceVec[l].fastEthernet.size(); m++)
                                {
                                    if (interface.name == uniqueDeviceVec[l].fastEthernet[m].name)
                                    {

                                        interface.defaultGateway = uniqueDeviceVec[l].fastEthernet[m].ipAddress;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    interface.connectedDevice = &netMerged[j].device1;
                    devConVec.push_back(DeviceConnection(uniqueDeviceVec[i], netMerged[j].device1, interface));
                    uniqueDeviceVec[i].fastEthernet.push_back(interface);
                }
                else
                {
                    Interface interface = Interface(getSerialConnName(uniqueDeviceVec[i].serial.size() + 1));
                    netMerged[j].curAvailableAddress = addNetId(netMerged[j].curAvailableAddress, 1);
                    interface.ipAddress = netMerged[j].curAvailableAddress;
                    interface.subMask = netMerged[j].mask;
                    interface.connectedDevice = &netMerged[j].device1;
                    devConVec.push_back(DeviceConnection(uniqueDeviceVec[i], netMerged[j].device1, interface));
                    uniqueDeviceVec[i].serial.push_back(interface);
                }
            }
        }
    }

    cout << "\nAddressing Table:\n";
    displayAddressingTable(uniqueDeviceVec);

    vector<Device> uniqueRouters;
    cout << "\nCommands for router configuration with it's own networks:";

    for (int i = 0; i < uniqueDeviceVec.size(); i++)
    {
        Device dev = uniqueDeviceVec[i];
        if (stringContains("PC", dev.name))
            continue;
        else
        {
            uniqueRouters.push_back(uniqueDeviceVec[i]);
            cout << "\nFor Router - " << dev.name << ":" << endl;
            cout << "No\nenable\nconfig terminal\nno ip domain-lookup\n";
            for (int j = 0; j < dev.serial.size(); j++)
            {
                cout << "interface " << dev.serial[j].name << endl;
                cout << "ip address " << dev.serial[j].ipAddress.to_str_without_prefix() << " " << dev.serial[j].subMask.to_str_without_prefix() << endl;
                cout << "no shutdown\nexit" << endl;
            }
            for (int j = 0; j < dev.fastEthernet.size(); j++)
            {
                cout << "interface " << dev.fastEthernet[j].name << endl;
                cout << "ip address " << dev.fastEthernet[j].ipAddress.to_str_without_prefix() << " " << dev.serial[j].subMask.to_str_without_prefix() << endl;
                cout << "no shutdown\nexit" << endl;
            }
        }
    }

    map<string, vector<Network>> devNetMap;
    for (int i = 0; i < uniqueRouters.size(); i++)
    {
        vector<Network> netsOfRouter;
        for (int j = 0; j < netMerged.size(); j++)
        {
            if (netMerged[j].device1.name == uniqueRouters[i].name || netMerged[j].device2.name == uniqueRouters[i].name)
            {
                netsOfRouter.push_back(netMerged[j]);
            }
        }
        devNetMap.insert(pair<string, vector<Network>>(uniqueRouters[i].name, netsOfRouter));
    }
    string commandsForRIPProtocolStr;
    cout << "\nCommands for router configuration with other networks:";

    for (int i = 0; i < uniqueDeviceVec.size(); i++)
    {
        Device dev = uniqueDeviceVec[i];
        if (stringContains("PC", dev.name))
            continue;
        else
        {
            cout << "\nFor Router - " << dev.name << ":" << endl;
            commandsForRIPProtocolStr = commandsForRIPProtocolStr + "\nFor Router - " + dev.name + ":\n" + "router rip\nversion 2\n";
            cout << "enable\nconfig terminal\n";
            for (int j = 0; j < netMerged.size(); j++)
            {
                // skipping own networks
                if (netMerged[j].device1.name == dev.name || netMerged[j].device2.name == dev.name)
                {
                    commandsForRIPProtocolStr = commandsForRIPProtocolStr + "network " + netMerged[j].ipAddress.to_str_without_prefix() + "\nno auto summery\n";
                    continue;
                }

                cout << "Conn. with " << netMerged[j].name << ":" << endl;
                cout << "ip route " << netMerged[j].ipAddress.to_str_without_prefix() << " " << netMerged[j].mask.to_str_without_prefix() << " ";
                Device destDev = Device("No device found");
                Device destDevPrev = Device("No Prev device found");
                visitedNet.clear();
                dfs(devNetMap, dev, destDev, destDevPrev, netMerged[j]);

                for (int k = 0; k < devConVec.size(); k++)
                {
                    if (devConVec[k].device1 == destDev && devConVec[k].device2 == destDevPrev)
                    {
                        cout << devConVec[k].interface.ipAddress.to_str_without_prefix();
                        break;
                    }
                }
                cout << endl;
            }
            commandsForRIPProtocolStr = commandsForRIPProtocolStr + "exit\nexit\ncopy run start\n";
            cout << "exit" << endl;
        }
    }

    cout << "--------------------------------------------------------------" << endl;

    cout << "\nCommands for router configuration with other networks\nUsing RIP (Routing Information Protocol):";
    cout << commandsForRIPProtocolStr << endl;
    return 0;
}