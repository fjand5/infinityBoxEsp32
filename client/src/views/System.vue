<template>
  <div class="system">
    <el-row :gutter="5">
      <el-col :span="24">
        <el-input placeholder="Router Wifi" v-model="ssid">
          <template slot="prepend">WIFI</template>
          <template slot="append">
             <el-button>
               OK
             </el-button>
          </template>
        </el-input>
      </el-col>
      <el-col :span="24">
        <el-input placeholder="Router Wifi" v-model="ssid">
          <template slot="prepend">WIFI</template>
          <template slot="append">
             <el-button>
               OK
             </el-button>
          </template>
        </el-input>
      </el-col>
    </el-row>
   
  </div>
</template>

<script>
export default {};
</script>

<style>
</style>