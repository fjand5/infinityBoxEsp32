<template>
  <div class="setting-box">
    <el-row>
      <el-col :span="3" style="line-height: 34px">Mode </el-col>
      <el-col :span="21">
        <el-select v-model="value" placeholder="Select" @change="selectMode">
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
      <el-col :span="4" style="line-height: 34px"
        >Time
      </el-col>
      <el-col :span="20">
        <el-slider :max="120" v-model="time" :step="10" show-stops> </el-slider>
      </el-col>
    </el-row>
  </div>
</template>

<script>
export default {
  data: function () {
    return {
      time: 0,
      value: -1,
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
        { value: 1, label: "Multi Dynamic" },
        { value: 1, label: "Rainbow" },
        { value: 1, label: "Rainbow Cycle" },
        { value: 1, label: "Scan" },
        { value: 1, label: "Dual Scan" },
        { value: 1, label: "Fade" },
        { value: 1, label: "Theater Chase" },
        { value: 1, label: "Theater Chase Rainbow" },
        { value: 1, label: "Running Lights" },
        { value: 1, label: "Twinkle" },
        { value: 2, label: "Twinkle Random" },
        { value: 2, label: "Twinkle Fade" },
        { value: 2, label: "Twinkle Fade Random" },
        { value: 2, label: "Sparkle" },
        { value: 2, label: "Flash Sparkle" },
        { value: 2, label: "Hyper Sparkle" },
        { value: 2, label: "Strobe" },
        { value: 2, label: "Strobe Rainbow" },
        { value: 2, label: "Multi Strobe" },
        { value: 2, label: "Blink Rainbow" },
        { value: 3, label: "Chase White" },
        { value: 3, label: "Chase Color" },
        { value: 3, label: "Chase Random" },
        { value: 3, label: "Chase Rainbow" },
        { value: 3, label: "Chase Flash" },
        { value: 3, label: "Chase Flash Random" },
        { value: 3, label: "Chase Rainbow White" },
        { value: 3, label: "Chase Blackout" },
        { value: 3, label: "Chase Blackout Rainbow" },
        { value: 3, label: "Color Sweep Random" },
        { value: 4, label: "Running Color" },
        { value: 4, label: "Running Red Blue" },
        { value: 4, label: "Running Random" },
        { value: 4, label: "Larson Scanner" },
        { value: 4, label: "Comet" },
        { value: 4, label: "Fireworks" },
        { value: 4, label: "Fireworks Random" },
        { value: 4, label: "Merry Christmas" },
        { value: 4, label: "Fire Flicker" },
        { value: 4, label: "Fire Flicker (soft)" },
        { value: 5, label: "Fire Flicker (intense)" },
        { value: 5, label: "Circus Combustus" },
        { value: 5, label: "Halloween" },
        { value: 5, label: "Bicolor Chase" },
        { value: 5, label: "Tricolor Chase" },
        { value: 5, label: "TwinkleFOX" },
        { value: 5, label: "Rain" },
      ],
    };
  },
};
</script>

<style>
.el-select {
  width: 100%;
}
.el-col {
  text-align: left;
  margin-bottom: 0 !important;
}
</style>