#ifndef DARWIN_H
#define DARWIN_H

#include <stdint.h>
#include <vector>

#include "CM730.h"
#include "MX28.h"
#include "FSR.h"

#include "DarwinRawSensors.h"

namespace Darwin {
    
    /**
     * Contains all of the dynamixel IDs in the system
     */
    namespace ID {
        enum ID {
            CM730 = 200,
            R_SHOULDER_PITCH = 1,
            L_SHOULDER_PITCH = 2,
            R_SHOULDER_ROLL = 3,
            L_SHOULDER_ROLL = 4,
            R_ELBOW = 5,
            L_ELBOW = 6,
            R_HIP_YAW = 7,
            L_HIP_YAW = 8,
            R_HIP_ROLL = 9,
            L_HIP_ROLL = 10,
            R_HIP_PITCH = 11,
            L_HIP_PITCH = 12,
            R_KNEE = 13,
            L_KNEE = 14,
            R_ANKLE_PITCH = 15,
            L_ANKLE_PITCH = 16,
            R_ANKLE_ROLL = 17,
            L_ANKLE_ROLL = 18,
            HEAD_PAN = 19,
            HEAD_TILT = 20,
            R_FSR = 111,
            L_FSR = 112,
            BROADCAST = 254
        };
    }
    
    /**
     * @brief The main class that others will use to interact with the CM730 and attached devices.
     *
     * @details
     *  This is the main access point for all users of this CM730 driver. Note that it is build for a little endian
     *  system, and if it is used on a big endian system, the code will need to be reviewed. This is because it is
     *  reading the 2 byte values as they are on the CM730 (which is little endian).
     *
     * @author Trent Houliston
     */
    class Darwin {
    private:
        /// Our UART class that we will communicate through
        UART m_uart;
        /// Our Prebuilt bulk read command
        std::vector<uint8_t> m_bulkReadCommand;
        
        /**
         * @brief Builds a bulk read packet to read all of the sensors.
         */
        void buildBulkReadPacket();
        
    public:
        /// The CM730
        CM730 m_cm730;
        /// The Right Shoulder Pitch MX28
        MX28 m_rShoulderPitch;
        /// The Left Shoulder Pitch MX28
        MX28 m_lShoulderPitch;
        /// The Right Shoulder Roll MX28
        MX28 m_rShoulderRoll;
        /// The Left Shoulder Roll MX28
        MX28 m_lShoulderRoll;
        /// The Right Elbow MX28
        MX28 m_rElbow;
        /// The Left Elbow MX28
        MX28 m_lElbow;
        /// The Right Hip Yaw MX28
        MX28 m_rHipYaw;
        /// The Left Hip Yaw MX28
        MX28 m_lHipYaw;
        /// The Right Hip Roll MX28
        MX28 m_rHipRoll;
        /// The Left Hip Roll MX28
        MX28 m_lHipRoll;
        /// The Right Hip Pitch MX28
        MX28 m_rHipPitch;
        /// The Left Hip Pitch MX28
        MX28 m_lHipPitch;
        /// The Right Knee MX28
        MX28 m_rKnee;
        /// The Left Knee MX28
        MX28 m_lKnee;
        /// The Right Ankle Pitch MX28
        MX28 m_rAnklePitch;
        /// The Left Ankle Pitch MX28
        MX28 m_lAnklePitch;
        /// The Right Ankle Roll MX28
        MX28 m_rAnkleRoll;
        /// The Left Ankle Roll MX28
        MX28 m_lAnkleRoll;
        /// The Head Pan MX28
        MX28 m_headPan;
        /// The Head Tilt MX28
        MX28 m_headTilt;
        /// The Right Foot FSR
        FSR m_rFSR;
        /// The Left Foot FSR
        FSR m_lFSR;
        
    public:
        /**
         * @brief Constructs a new Darwin instance and sets up communication with the CM730.
         * 
         * @param name the file handle for the device the CM730 is connected to (e.g. /dev/ttyUSB0)
         */
        Darwin(const char* name);
        
        /**
         * @brief Pings all of the attached devices, and returns a map containing their ID and if they were contactable.
         *
         * @returns a map containing IDs and if they were contactable (returned no error code)
         */
        std::vector<std::pair<uint8_t, bool>> selfTest();
        
        /**
         * @brief This reads all of the sensors in a predefined pattern of what is considered "Interesting"
         *
         * @returns A BulkReadResuts object containing all of the sensor data as it was read from the device (no trasforms)
         */
        BulkReadResults bulkRead();
        
        /**
         * @brief This writes a series of motor values to the device
         *
         * @param motors The motor objects to write
         */
        void writeMotors(const std::vector<Types::MotorValues>& motors);
    };
}

#endif