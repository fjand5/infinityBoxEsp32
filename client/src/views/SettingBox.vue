<template>
  <div class="setting-box">
    <el-row>
      <el-col :span="4" style="line-height: 34px">Mode </el-col>
      <el-col :span="19">
        <el-select
          v-model="mode"
          placeholder="Select"
          @change="sendModeCommand"
        >
          <el-option
            v-for="item in options"
            :key="item.value"
            :label="item.label"
            :value="item.value"
          >
          </el-option>
        </el-select>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="4" style="line-height: 34px">Timer </el-col>
      <el-col :span="19">
        <el-slider
          @change="sendTimerCommand"
          :max="120"
          v-model="timer"
          :step="10"
          show-stops
        >
        </el-slider>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="4" style="line-height: 34px">Bright </el-col>
      <el-col :span="19">
        <el-slider @change="sendBrightCommand" :max="100" v-model="bright">
        </el-slider>
      </el-col>
    </el-row>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

export default {
  data: function () {
    return {
      debounceBrightTimer: undefined,
      debounceTimerTimer: undefined,

      timer: 0,
      bright: 0,
      mode: -1,
      options: [
        { value: -1, label: "OFF" },
        { value: 0, label: "Static" },
        { value: 1, label: "Blink" },
        { value: 2, label: "Breath" },
        { value: 3, label: "Color Wipe" },
        { value: 4, label: "Color Wipe Inverse" },
        { value: 5, label: "Color Wipe Reverse" },
        { value: 6, label: "Color Wipe Reverse Inverse" },
        { value: 7, label: "Color Wipe Random" },
        { value: 8, label: "Random Color" },
        { value: 9, label: "Single Dynamic" },
        { value: 10, label: "Multi Dynamic" },
        { value: 11, label: "Rainbow" },
        { value: 12, label: "Rainbow Cycle" },
        { value: 13, label: "Scan" },
        { value: 14, label: "Dual Scan" },
        { value: 15, label: "Fade" },
        { value: 16, label: "Theater Chase" },
        { value: 17, label: "Theater Chase Rainbow" },
        { value: 18, label: "Running Lights" },
        { value: 19, label: "Twinkle" },
        { value: 20, label: "Twinkle Random" },
        { value: 21, label: "Twinkle Fade" },
        { value: 22, label: "Twinkle Fade Random" },
        { value: 23, label: "Sparkle" },
        { value: 24, label: "Flash Sparkle" },
        { value: 25, label: "Hyper Sparkle" },
        { value: 26, label: "Strobe" },
        { value: 27, label: "Strobe Rainbow" },
        { value: 28, label: "Multi Strobe" },
        { value: 29, label: "Blink Rainbow" },
        { value: 30, label: "Chase White" },
        { value: 31, label: "Chase Color" },
        { value: 32, label: "Chase Random" },
        { value: 33, label: "Chase Rainbow" },
        { value: 34, label: "Chase Flash" },
        { value: 35, label: "Chase Flash Random" },
        { value: 36, label: "Chase Rainbow White" },
        { value: 37, label: "Chase Blackout" },
        { value: 38, label: "Chase Blackout Rainbow" },
        { value: 39, label: "Color Sweep Random" },
        { value: 40, label: "Running Color" },
        { value: 41, label: "Running Red Blue" },
        { value: 42, label: "Running Random" },
        { value: 43, label: "Larson Scanner" },
        { value: 44, label: "Comet" },
        { value: 45, label: "Fireworks" },
        { value: 46, label: "Fireworks Random" },
        { value: 47, label: "Merry Christmas" },
        { value: 48, label: "Fire Flicker" },
        { value: 49, label: "Fire Flicker (soft)" },
        { value: 50, label: "Fire Flicker (intense)" },
        { value: 51, label: "Circus Combustus" },
        { value: 52, label: "Halloween" },
        { value: 53, label: "Bicolor Chase" },
        { value: 54, label: "Tricolor Chase" },
        { value: 55, label: "TwinkleFOX" },
        { value: 56, label: "Rain" },
      ],
    };
  },
  mounted: function () {
    this.bright = parseInt(this.getData.brightness_sld);
    if (this.getData.on_off_tgl == "false") {
      this.mode = -1;
    } else {
      this.mode = parseInt(this.getData.current_mode);
    }

    if (this.getData.timer_tgl == "false") {
      this.timer = 0;
    } else {
      this.timer = parseInt(this.getData.timer_sld);
    }
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  watch: {
    getData: function (n) {
      this.bright = parseInt(n.brightness_sld);
      if (n.on_off_tgl == "false") {
        this.mode = -1;
      } else {
        this.mode = parseInt(n.current_mode);
      }
      if (n.timer_tgl == "false") {
        this.timer = 0;
      } else {
        this.timer = parseInt(n.timer_sld);
      }

      // this.clientValue = this.espValue;
      // setTimeout(() => {
      //   clearTimeout(this.debounceTimer);
      // }, 90);
    },
  },
  methods: {
    sendBrightCommand: function () {
      clearTimeout(this.debounceBrightTimer);
      this.debounceBrightTimer = setTimeout(() => {
        this.$store.dispatch("sendCommand", {
          espKey: "brightness_sld",
          espValue: this.bright,
        });
      }, 100);
    },
    sendTimerCommand: function () {
      clearTimeout(this.debounceTimerTimer);
      this.debounceTimerTimer = setTimeout(() => {
        if (this.timer == 0) {
          this.$store.dispatch("sendCommand", {
            espKey: "timer_tgl",
            espValue: "false",
          });
        } else {
          if (this.getData.timer_tgl == "false") {
            this.$store.dispatch("sendCommand", {
              espKey: "timer_tgl",
              espValue: "true",
            });
          }
          this.$store.dispatch("sendCommand", {
            espKey: "timer_sld",
            espValue: this.timer,
          });
        }
      }, 100);
    },
    sendModeCommand: function () {
      if (this.mode == -1) {
        this.$store.dispatch("sendCommand", {
          espKey: "on_off_tgl",
          espValue: "false",
        });
      } else {
        if (this.getData.on_off_tgl == "false") {
          this.$store.dispatch("sendCommand", {
            espKey: "on_off_tgl",
            espValue: "true",
          });
        }
        this.$store.dispatch("sendCommand", {
          espKey: "current_mode",
          espValue: this.mode,
        });
      }
    },
  },
};
</script>

<style>
.el-select {
  width: 100%;
}

.setting-box {
  padding: 12px 2px;
}
.el-col {
  text-align: left;
  margin-bottom: 0 !important;
}
</style>