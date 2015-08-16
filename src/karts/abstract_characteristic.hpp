//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006-2015 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_ABSTRACT_CHARACTERISTICS_HPP
#define HEADER_ABSTRACT_CHARACTERISTICS_HPP

#include <string>
#include <vector>

class SkiddingProperties;
class InterpolationArray;

/**
 * Characteristics are the properties of a kart that influence
 * gameplay mechanics.
 * The biggest parts are:
 * - Physics
 * - Visuals
 * - Items
 * - and miscellaneous properties like nitro and startup boost.
 *
 * The documentation of these properties can be found in
 * the kart_characteristics.xml file.
 * Large parts of this file are generated by tools/create_kart_properties.py.
 * Please don't change the generated code here, instead change the script,
 * regenerate the code and overwrite the whole generated part with the result.
 */
class AbstractCharacteristic
{
public:
    union Value
    {
        float *f;
        bool *b;
        std::vector<float> *fv;
        InterpolationArray *ia;

        Value(float *f) : f(f) {}
        Value(bool *b) : b(b) {}
        Value(std::vector<float> *fv) : fv(fv) {}
        Value(InterpolationArray *ia) : ia(ia) {}
    };

    enum ValueType
    {
        TYPE_FLOAT,
        TYPE_BOOL,
        TYPE_FLOAT_VECTOR,
        TYPE_INTERPOLATION_ARRAY
    };

    enum CharacteristicType
    {
        // Script-generated content generated by tools/create_kart_properties.py enum
        // Please don't change the following tag. It will be automatically detected
        // by the script and replace the contained content.
        // To update the code, use tools/update_characteristics.py
        /* <characteristics-start enum> */

        // Suspension
        SUSPENSION_STIFFNESS,
        SUSPENSION_REST,
        SUSPENSION_TRAVEL,
        SUSPENSION_EXP_SPRING_RESPONSE,
        SUSPENSION_MAX_FORCE,

        // Stability
        STABILITY_ROLL_INFLUENCE,
        STABILITY_CHASSIS_LINEAR_DAMPING,
        STABILITY_CHASSIS_ANGULAR_DAMPING,
        STABILITY_DOWNWARD_IMPULSE_FACTOR,
        STABILITY_TRACK_CONNECTION_ACCEL,
        STABILITY_SMOOTH_FLYING_IMPULSE,

        // Turn
        TURN_RADIUS,
        TURN_TIME_RESET_STEER,
        TURN_TIME_FULL_STEER,

        // Engine
        ENGINE_POWER,
        ENGINE_MAX_SPEED,
        ENGINE_BRAKE_FACTOR,
        ENGINE_BRAKE_TIME_INCREASE,
        ENGINE_MAX_SPEED_REVERSE_RATIO,

        // Gear
        GEAR_SWITCH_RATIO,
        GEAR_POWER_INCREASE,

        // Mass
        MASS,

        // Wheels
        WHEELS_DAMPING_RELAXATION,
        WHEELS_DAMPING_COMPRESSION,

        // Camera
        CAMERA_DISTANCE,
        CAMERA_FORWARD_UP_ANGLE,
        CAMERA_BACKWARD_UP_ANGLE,

        // Jump
        JUMP_ANIMATION_TIME,

        // Lean
        LEAN_MAX,
        LEAN_SPEED,

        // Anvil
        ANVIL_DURATION,
        ANVIL_WEIGHT,
        ANVIL_SPEED_FACTOR,

        // Parachute
        PARACHUTE_FRICTION,
        PARACHUTE_DURATION,
        PARACHUTE_DURATION_OTHER,
        PARACHUTE_LBOUND_FRACTION,
        PARACHUTE_UBOUND_FRACTION,
        PARACHUTE_MAX_SPEED,

        // Bubblegum
        BUBBLEGUM_DURATION,
        BUBBLEGUM_SPEED_FRACTION,
        BUBBLEGUM_TORQUE,
        BUBBLEGUM_FADE_IN_TIME,
        BUBBLEGUM_SHIELD_DURATION,

        // Zipper
        ZIPPER_DURATION,
        ZIPPER_FORCE,
        ZIPPER_SPEED_GAIN,
        ZIPPER_MAX_SPEED_INCREASE,
        ZIPPER_FADE_OUT_TIME,

        // Swatter
        SWATTER_DURATION,
        SWATTER_DISTANCE,
        SWATTER_SQUASH_DURATION,
        SWATTER_SQUASH_SLOWDOWN,

        // Plunger
        PLUNGER_BAND_MAX_LENGTH,
        PLUNGER_BAND_FORCE,
        PLUNGER_BAND_DURATION,
        PLUNGER_BAND_SPEED_INCREASE,
        PLUNGER_BAND_FADE_OUT_TIME,
        PLUNGER_IN_FACE_TIME,

        // Startup
        STARTUP_TIME,
        STARTUP_BOOST,

        // Rescue
        RESCUE_DURATION,
        RESCUE_VERT_OFFSET,
        RESCUE_HEIGHT,

        // Explosion
        EXPLOSION_DURATION,
        EXPLOSION_RADIUS,
        EXPLOSION_INVULNERABILITY_TIME,

        // Nitro
        NITRO_DURATION,
        NITRO_ENGINE_FORCE,
        NITRO_CONSUMPTION,
        NITRO_SMALL_CONTAINER,
        NITRO_BIG_CONTAINER,
        NITRO_MAX_SPEED_INCREASE,
        NITRO_FADE_OUT_TIME,
        NITRO_MAX,

        // Slipstream
        SLIPSTREAM_DURATION,
        SLIPSTREAM_LENGTH,
        SLIPSTREAM_WIDTH,
        SLIPSTREAM_COLLECT_TIME,
        SLIPSTREAM_USE_TIME,
        SLIPSTREAM_ADD_POWER,
        SLIPSTREAM_MIN_SPEED,
        SLIPSTREAM_MAX_SPEED_INCREASE,
        SLIPSTREAM_FADE_OUT_TIME,

        /* <characteristics-end enum> */


        // Count
        CHARACTERISTIC_COUNT
    };
private:
    /** The skididing properties for this kart, as a separate object in order
     *  to reduce dependencies (and therefore compile time) when changing
     *  any skidding property. */
    //TODO SkiddingProperties *m_skidding;

public:
    AbstractCharacteristic();
    virtual ~AbstractCharacteristic() {}

    virtual const SkiddingProperties* getSkiddingProperties() const;

    /**
     * The process function is the core of this characteristics system.
     * Any computation of the properties should happen here and modify the
     * values of the value-pointer (be sure to use the right type!) and the
     * is_set parameter when the value was set by the call (and wasn't set
     * before).
     *
     * \param type The characteristic that should be modified.
     * \param value The current value and result at the same time.
     * \param is_set If the current value was already set (so it can be used
     *              for computations).
     */
    virtual void process(CharacteristicType type, Value value, bool *is_set) const;

    static ValueType getType(CharacteristicType type);
    static std::string getName(CharacteristicType type);

    // Script-generated content generated by tools/create_kart_properties.py defs
    // Please don't change the following tag. It will be automatically detected
    // by the script and replace the contained content.
    // To update the code, use tools/update_characteristics.py
    /* <characteristics-start defs> */

    float getSuspensionStiffness() const;
    float getSuspensionRest() const;
    float getSuspensionTravel() const;
    bool getSuspensionExpSpringResponse() const;
    float getSuspensionMaxForce() const;

    float getStabilityRollInfluence() const;
    float getStabilityChassisLinearDamping() const;
    float getStabilityChassisAngularDamping() const;
    float getStabilityDownwardImpulseFactor() const;
    float getStabilityTrackConnectionAccel() const;
    float getStabilitySmoothFlyingImpulse() const;

    InterpolationArray getTurnRadius() const;
    float getTurnTimeResetSteer() const;
    InterpolationArray getTurnTimeFullSteer() const;

    float getEnginePower() const;
    float getEngineMaxSpeed() const;
    float getEngineBrakeFactor() const;
    float getEngineBrakeTimeIncrease() const;
    float getEngineMaxSpeedReverseRatio() const;

    std::vector<float> getGearSwitchRatio() const;
    std::vector<float> getGearPowerIncrease() const;

    float getMass() const;

    float getWheelsDampingRelaxation() const;
    float getWheelsDampingCompression() const;

    float getCameraDistance() const;
    float getCameraForwardUpAngle() const;
    float getCameraBackwardUpAngle() const;

    float getJumpAnimationTime() const;

    float getLeanMax() const;
    float getLeanSpeed() const;

    float getAnvilDuration() const;
    float getAnvilWeight() const;
    float getAnvilSpeedFactor() const;

    float getParachuteFriction() const;
    float getParachuteDuration() const;
    float getParachuteDurationOther() const;
    float getParachuteLboundFraction() const;
    float getParachuteUboundFraction() const;
    float getParachuteMaxSpeed() const;

    float getBubblegumDuration() const;
    float getBubblegumSpeedFraction() const;
    float getBubblegumTorque() const;
    float getBubblegumFadeInTime() const;
    float getBubblegumShieldDuration() const;

    float getZipperDuration() const;
    float getZipperForce() const;
    float getZipperSpeedGain() const;
    float getZipperMaxSpeedIncrease() const;
    float getZipperFadeOutTime() const;

    float getSwatterDuration() const;
    float getSwatterDistance() const;
    float getSwatterSquashDuration() const;
    float getSwatterSquashSlowdown() const;

    float getPlungerBandMaxLength() const;
    float getPlungerBandForce() const;
    float getPlungerBandDuration() const;
    float getPlungerBandSpeedIncrease() const;
    float getPlungerBandFadeOutTime() const;
    float getPlungerInFaceTime() const;

    std::vector<float> getStartupTime() const;
    std::vector<float> getStartupBoost() const;

    float getRescueDuration() const;
    float getRescueVertOffset() const;
    float getRescueHeight() const;

    float getExplosionDuration() const;
    float getExplosionRadius() const;
    float getExplosionInvulnerabilityTime() const;

    float getNitroDuration() const;
    float getNitroEngineForce() const;
    float getNitroConsumption() const;
    float getNitroSmallContainer() const;
    float getNitroBigContainer() const;
    float getNitroMaxSpeedIncrease() const;
    float getNitroFadeOutTime() const;
    float getNitroMax() const;

    float getSlipstreamDuration() const;
    float getSlipstreamLength() const;
    float getSlipstreamWidth() const;
    float getSlipstreamCollectTime() const;
    float getSlipstreamUseTime() const;
    float getSlipstreamAddPower() const;
    float getSlipstreamMinSpeed() const;
    float getSlipstreamMaxSpeedIncrease() const;
    float getSlipstreamFadeOutTime() const;

    /* <characteristics-end defs> */
};

#endif

