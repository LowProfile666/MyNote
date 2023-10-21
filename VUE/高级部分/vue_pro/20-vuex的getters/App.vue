<template>
    <div>
		<User></User>
		<hr>
		<Vip></Vip>
		<hr>
		<Name></Name>
    </div>
</template>

<script>
	import User from './components/User'
	import Vip from './components/Vip'
	import Name from './components/Name'

	export default {
		name : 'App',
		components : {User, Vip, Name}
	}
</script>