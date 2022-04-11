<template>
  <div class="music-reaction">
    <el-row>
      <el-col :span="4" style="line-height: 34px">Gain </el-col>
      <el-col :span="20">
        <el-slider @change="sendGainCommand" v-model="gian"></el-slider>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="4" style="line-height: 34px">Beat </el-col>
      <el-col :span="20">
        <el-slider @change="sendBeatCommand" v-model="beat"></el-slider>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="4" style="line-height: 34px">Mode </el-col>
      <el-col :span="20">
        <el-select v-model="mode" placeholder="Select" @change="selectMode">
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
  </div>
</template>

<script>
import { mapGetters } from "vuex";

export default {
  data: function () {
    return {
      debounceGainTimer: undefined,
      debounceBeatTimer: undefined,

      gian: 0,
      beat: 0,
      mode: -1,
      options: [
        {
          value: -1,
          label: "OFF",
        },
        {
          value: 0,
          label: "Light Years Ahead",
        },
        {
          value: 1,
          label: "Elliptical Circuit",
        },
        {
          value: 2,
          label: "The Magnetars",
        },
        {
          value: 3,
          label: "Flyby Voyagers",
        },
        {
          value: 4,
          label: "Halo of Stars",
        },
        {
          value: 5,
          label: "Stellar Remnants",
        },
        {
          value: 6,
          label: "The Satellite Set",
        },
        {
          value: 7,
          label: "Marvelous Martians",
        },
        {
          value: 8,
          label: "Exploding Stars",
        },
        {
          value: 9,
          label: "The Lava Planets",
        },
        {
          value: 10,
          label: "Mars Attacks",
        },
        {
          value: 11,
          label: "The Dark Energy Stars",
        },
        {
          value: 12,
          label: "Cosmic Rays",
        },
        {
          value: 13,
          label: "The Omega Nebula",
        },
      ],
    };
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  mounted: function () {
    this.gian = parseInt(this.getData.micGain_sld);
    this.beat = parseInt(this.getData.takeBeat_sld);
    this.mode = parseInt(this.getData.cur_music_mode);
  },
  methods: {
    sendGainCommand: function () {
      clearTimeout(this.debounceGainTimer);
      this.debounceGainTimer = setTimeout(() => {
        this.$store.dispatch("sendCommand", {
          espKey: "micGain_sld",
          espValue: this.gian,
        });
      }, 100);
    },
    sendBeatCommand: function () {
      clearTimeout(this.debounceBeatTimer);
      this.debounceBeatTimer = setTimeout(() => {
        this.$store.dispatch("sendCommand", {
          espKey: "takeBeat_sld",
          espValue: this.beat,
        });
      }, 100);
    },
    selectMode: function (val) {
      if (val == -1) {
        this.$store.dispatch("sendCommand", {
          espKey: "react_music",
          espValue: "false",
        });
      } else {
        if (this.getData.react_music == "false") {
          this.$store.dispatch("sendCommand", {
            espKey: "react_music",
            espValue: "true",
          });
        }
           this.$store.dispatch("sendCommand", {
            espKey: "music_mode_" + val,
            espValue: "n/a",
          });
      }
    },
  },
};
</script>

<style >
.el-select {
  width: 100%;
}
.music-reaction {
  padding: 12px 2px;
}
.el-col {
  text-align: left;
  margin-bottom: 0 !important;
}
</style>