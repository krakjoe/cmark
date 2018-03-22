--TEST--
CommonMark\Node isset previous
--FILE--
<?php
$doc = new CommonMark\Node\Document();
$doc->appendChild(new CommonMark\Node\Paragraph);
$doc->appendChild(
	$para = new CommonMark\Node\Paragraph);

$f = function() use($para) {
	return isset($para->previous);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
