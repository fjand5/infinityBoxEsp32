<template>
  <div class="color">
    <el-row :gutter="20">
      <el-col :span="6">
        <el-select v-model="value" placeholder="Select"
        @change="selectColor"
        >
          <el-option
            v-for="item in options"
            :key="item.value"
            :value="item.value"
          >
          </el-option>
        </el-select>
      </el-col>
      <el-col :span="6">
        <el-color-picker v-model="color1"></el-color-picker>
      </el-col>
      <el-col :span="6">
        <el-color-picker v-model="color2"></el-color-picker>
      </el-col>
      <el-col :span="6">
        <el-color-picker v-model="color3"></el-color-picker>
      </el-col>
    </el-row>
  </div>
</template>

<script>
export default {
  data: function () {
    return {
      color1: "",
      color2:"",
      color3:"",
      value: 0,
      options: [],
    };
  },
  mounted:function(){
    for (let index = 0; index < 15; index++) {
      const element = {
        value: index
      }
      this.options.push(element)
    }
  },
  methods:{
    selectColor: function(val){
      console.log(val)
    }
  }
};
</script>

<style>
</style>