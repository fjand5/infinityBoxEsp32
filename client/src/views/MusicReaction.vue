<template>
  <div class="music-reaction">
    <el-row>
      <el-col :span="4" :pull="1" style="line-height: 34px">Gain </el-col>
      <el-col :span="20">
        <el-slider v-model="gian"></el-slider>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="4" :pull="1" style="line-height: 34px">Beat </el-col>
      <el-col :span="20">
        <el-slider v-model="beat"></el-slider>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="4" :pull="1" style="line-height: 34px">Mode </el-col>
      <el-col :span="20">
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
  </div>
</template>

<script>
export default {
  data: function () {
    return {
      gian: 0,
      beat: 0,
      value: -1,
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
  mounted: function () {},
  methods: {
    selectMode: function () {},
  },
};
</script>

<style >
.el-select {
  width: 100%;
}
.music-reaction {
  padding: 25px 10px;
}
.el-col {
  margin-bottom: 0 !important;
}
</style>