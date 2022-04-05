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
      value: 0,
      options: [
        {
          value: 0,
          label: "OFF"
        },
        {
          value: 1,
          label: "1"
        },
        ],
    };
  },
  mounted:function(){
  },
  methods:{
    selectMode:function(){

    }
  }
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