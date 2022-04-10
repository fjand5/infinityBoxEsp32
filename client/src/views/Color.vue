<template>
  <div class="color">
    <el-row :gutter="20">
      <el-col :span="6">
        <!-- <el-select v-model="value" placeholder="Select" @change="selectColor">
          <el-option
            v-for="item in options"
            :key="item.value"
            :value="item.value"
          >
          </el-option>
        </el-select> -->
        <el-switch v-model="timer" @change="setTimer" inactive-text="Timer"> </el-switch>
      </el-col>
      <el-col :span="6" :push="1">
        <el-color-picker v-model="color1"></el-color-picker>
      </el-col>
      <el-col :span="6" :push="1">
        <el-color-picker v-model="color2"></el-color-picker>
      </el-col>
      <el-col :span="6" :push="1">
        <el-color-picker v-model="color3"></el-color-picker>
      </el-col>
    </el-row>
    <!-- <el-row>
      <el-col :span="4" style="line-height: 34px">Timer </el-col>
      <el-col :span="19">
        <el-slider :max="120" v-model="timer" :step="10" show-stops>
        </el-slider>
      </el-col>
    </el-row> -->
  </div>
</template>

<script>
import { mapGetters } from "vuex";
export default {
  data: function () {
    return {
      debounceTimerTimer: undefined,
      timer: true,
      color1: "",
      color2: "",
      color3: "",
      value: 0,
      options: [],
    };
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  mounted: function () {
    for (let index = 0; index < 15; index++) {
      const element = {
        value: index,
      };
      this.options.push(element);
    }
    this.color1 = this.getData.color1_inp;
    this.color2 = this.getData.color2_inp;
    this.color3 = this.getData.color3_inp;
    this.timer = this.getData.color_timer == "true";
  },
  watch: {
    getData: function (n) {
      this.color1 = n.color1_inp;
      this.color2 = n.color2_inp;
      this.color3 = n.color3_inp;
      this.timer = n.color_timer == "true";
    },
  },
  methods: {
    setTimer: function (val) {
      console.log(val);
      this.$store.dispatch("sendCommand", {
        espKey: "color_timer",
        espValue: val.toString(),
      });
    },
  },
};
</script>

<style>
.el-switch {
  top: 10px !important;
}
.el-row {
  margin-top: 12px;
}
.color {
  padding: 12px 2px;
  text-align: left;
}
</style>