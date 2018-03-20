--TEST--
CommonMark\Node\CodeBlock fetch fence cached
--FILE--
<?php
$md = <<<MD
```
code
```
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

$child = $doc->firstChild;

if ($child instanceof CommonMark\Node\CodeBlock) {
	$f = function() use($child) {
		return $child->fence;
	};
	
	$f();
	$f();

	echo "OK";
}
?>
--EXPECT--
OK
