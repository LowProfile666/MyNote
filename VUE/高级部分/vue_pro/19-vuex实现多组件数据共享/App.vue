<template>
    <div>
		<User></User>
		<hr>
		<Vip></Vip>
    </div>
</template>

<script>
	import User from './components/User'
	import Vip from './components/Vip'

	export default {
		name : 'App',
		components : {User, Vip}
	}
</script>