--TEST--
CommonMark\Node fetch HTMLBlock
--FILE--
<?php
$md = <<<MD
<html>
 block here
</html>
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->getFirstChild() instanceof CommonMark\Node\HTMLBlock) {
	echo "OK";
}
?>
--EXPECT--
OK
